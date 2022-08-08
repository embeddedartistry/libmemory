/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include <assert.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdint.h>
#include <threadx/tx_api.h>

#pragma mark - Declarations -

/// ThreadX internal memory pool stucture
static TX_BYTE_POOL malloc_pool_;

/**
 * Flag that is used in malloc() to cause competing threads to wait until
 * initialization is completed before allocating memory.
 */
static volatile bool initialized_ = false;

#pragma mark - APIs -

__attribute__((weak)) void malloc_init(void)
{
	// Unused here, override to specify your own init functin
	// Which includes malloc_addblock calls
}

/**
 * malloc_addblock must be called before memory allocation calls are made.
 * In this ThreadX implementation, malloc() calls will block until memory
 * has been allocated
 */
void malloc_addblock(void* addr, size_t size)
{
	assert(addr && (size > 0));

	/*
	 * tx_byte_pool_create is ThreadX's API to create a byte pool using a memory block.
	 * We are essentially just wrapping ThreadX APIs into a simpler form
	 */
	unsigned return_code = tx_byte_pool_create(&malloc_pool_, "Heap Memory Pool", addr, size);
	assert(return_code == TX_SUCCESS);

	// Signal to any threads waiting on do_malloc that we are done
	initialized_ = true;
}

void* malloc(size_t size)
{
	void* ptr = NULL;

	/**
	 * In the ThreadX implementaiton, we make sure the ThreadX pool has been
	 * created before we try to allocate memory, or there will be an error.
	 * We sleep our threads until memory has been added.
	 */
	while(!initialized_)
	{
		tx_thread_sleep(1);
	}

	if(size > 0)
	{
		// We simply wrap the threadX call into a standard form
		unsigned return_code = tx_byte_allocate(&malloc_pool_, &ptr, size, TX_WAIT_FOREVER);

		// I add the string to provide a more helpful error output.  It's value is always true.
		assert(return_code == TX_SUCCESS && "malloc failed");
	} // else NULL if there was an error

	return ptr;
}

void free(void* ptr)
{
	/// free should NEVER be called before malloc is init'd
	assert(initialized_);

	if(ptr)
	{
		// We simply wrap the threadX call into a standard form
		unsigned return_code = tx_byte_release(ptr);
		assert(return_code == TX_SUCCESS);
	}
}
