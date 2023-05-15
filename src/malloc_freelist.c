/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include <linkedlist/ll.h>
#include <malloc.h>
#include <stdint.h>

/// By default, the freelist is declared as static so that it cannot be accessed
/// outside of the library. Users who wish to override this default declaration
/// can define `FREELIST_DECL_SPECIFIERS` to use an alternative.
/// One option is to make it an empty definition to make it publicly visible,
/// which may be useful for capturing state or performing metadata analysis.
///
/// Unless you have a specific use case, we recommend sticking with the default.
#ifndef FREELIST_DECL_SPECIFIERS
#define FREELIST_DECL_SPECIFIERS static
#endif

#pragma mark - Definitions -

/**
 * Simple macro for making sure memory addresses are aligned
 * to the nearest power of two
 */
#ifndef align_up
#define align_up(num, align) (((num) + ((align)-1)) & ~((align)-1))
#endif

/*
 * This is the container for our free-list.
 * Note the usage of the linked list here: the library uses offsetof
 * and container_of to manage the list and get back to the parent struct.
 */
typedef struct
{
	ll_t node;
	size_t size;
	char* block;
} alloc_node_t;

/**
 * We vend a memory address to the user.  This lets us translate back and forth
 * between the vended pointer and the container we use for managing the data.
 */
#define ALLOC_HEADER_SZ offsetof(alloc_node_t, block)

// We are enforcing a minimum allocation size of 32B.
#define MIN_ALLOC_SZ ALLOC_HEADER_SZ + 32

#pragma mark - Prototypes -

static void defrag_free_list(void);

/**
 * @brief Lock malloc (for thread safety.)
 *
 * Weakly linked, can be overridden based on your needs.
 * By default, this implementation is not thread safe, and malloc_lock() is a no-op.
 * If you need a thread-safe version, define the function for your system - it should
 * lock a mutex.
 *
 * @post The lock is held by a single thread.
 */
void malloc_lock();

/**
 * @brief Unlock malloc (for thread safety)
 *
 * Weakly linked, can be overridden based on your needs.
 * By default, this implementation is not thread safe, and malloc_unlock() is a no-op.
 * If you need a thread-safe version, define the function for your system - it should
 * unlock a mutex.
 *
 * @post The lock is released.
 */
void malloc_unlock();

#pragma mark - Declarations -

// This macro simply declares and initializes our linked list
FREELIST_DECL_SPECIFIERS LIST_INIT(free_list);

#pragma mark - Private Functions -

/**
 * When we free, we can take our node and check to see if any memory blocks
 * can be combined into larger blocks.  This will help us fight against
 * memory fragmentation in a simple way.
 */
void defrag_free_list(void)
{
	alloc_node_t* block = NULL;
	alloc_node_t* last_block = NULL;
	alloc_node_t* temp = NULL;

	list_for_each_entry_safe(block, temp, &free_list, node)
	{
		if(last_block)
		{
			if((((uintptr_t)&last_block->block) + last_block->size) == (uintptr_t)block)
			{
				last_block->size += ALLOC_HEADER_SZ + block->size;
				list_del(&block->node);
				continue;
			}
		}
		last_block = block;
	}
}

#pragma mark - APIs -

__attribute__((weak)) void malloc_init(void)
{
	// Unused here, override to specify your own init function
	// Which includes malloc_addblock calls
}

__attribute__((weak)) void malloc_lock()
{
	// Intentional no-op
}

__attribute__((weak)) void malloc_unlock()
{
	// Intentional no-op
}

void* malloc(size_t size)
{
	void* ptr = NULL;
	alloc_node_t* found_block = NULL;

	if(size > 0)
	{
		// Align the pointer
		size = align_up(size, sizeof(void*));

		malloc_lock();

		// try to find a big enough block to alloc
		list_for_each_entry(found_block, &free_list, node)
		{
			if(found_block->size >= size)
			{
				ptr = &found_block->block;
				break;
			}
		}

		// we found something
		if(ptr)
		{
			// Can we split the block?
			if((found_block->size - size) >= MIN_ALLOC_SZ)
			{
				alloc_node_t* new_block = (alloc_node_t*)((uintptr_t)(&found_block->block) + size);
				new_block->size = found_block->size - size - ALLOC_HEADER_SZ;
				found_block->size = size;
				list_insert(&new_block->node, &found_block->node, found_block->node.next);
			}

			list_del(&found_block->node);
		}

		malloc_unlock();

	} // else NULL

	return ptr;
}

void free(void* ptr)
{
	// Don't free a NULL pointer..
	if(ptr)
	{
		// we take the pointer and use container_of to get the corresponding alloc block
		alloc_node_t* current_block = container_of(ptr, alloc_node_t, block);
		alloc_node_t* free_block = NULL;

		malloc_lock();

		// Let's put it back in the proper spot
		list_for_each_entry(free_block, &free_list, node)
		{
			if(free_block > current_block)
			{
				list_insert(&current_block->node, free_block->node.prev, &free_block->node);
				goto blockadded;
			}
		}
		list_add_tail(&current_block->node, &free_list);

	blockadded:
		// Let's see if we can combine any memory
		defrag_free_list();

		malloc_unlock();
	}
}

void malloc_addblock(void* addr, size_t size)
{
	// let's align the start address of our block to the next pointer aligned number
	alloc_node_t* new_memory_block = (void*)align_up((uintptr_t)addr, sizeof(void*));

	// calculate actual size - remove our alignment and our header space from the availability
	new_memory_block->size = (uintptr_t)addr + size - (uintptr_t)new_memory_block - ALLOC_HEADER_SZ;

	// and now our giant block of memory is added to the list!
	malloc_lock();
	list_add(&new_memory_block->node, &free_list);
	malloc_unlock();
}
