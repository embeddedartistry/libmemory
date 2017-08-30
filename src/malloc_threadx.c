/*
* Copyright © 2017 Embedded Artistry LLC.
* License: MIT. See LICENSE file for details.
*/

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <threadx/tx_api.h>

#pragma mark - Definitions -

/*
* In this example, I am using the compiler's builtin atomic compare and swap
* Routine. This will provide atomic access to swapping the malloc pointer,
* and only one function will initialize the memory pool.
*/
#define atomic_compare_and_swap __sync_val_compare_and_swap

#pragma mark - Prototypes -

#pragma mark - Declarations -

// ThreadX internal memory pool stucture
static TX_BYTE_POOL malloc_pool_ = {0};

/*
* Flag that is used in do_malloc() to cause competing threads to wait until
* initialization is completed before allocating memory.
*/
volatile static bool initialized_ = false;

#pragma mark - Private Functions -

/*
 * init_malloc must be called before memory allocation calls are made
 * This sets up a byte pool for the heap using the defined HEAP_START and HEAP_END macros
 * Size is passed to do_malloc and allocated to the caller
 */

void malloc_addblock(void* addr, size_t size)
{
	assert(addr && (size > 0));

	uint8_t r;

	/**
	* This is ThreadX's API to create a byte pool using a memory block.
	* We are essentially just wrapping ThreadX APIs into a simpler form
	*/
	r = tx_byte_pool_create(&malloc_pool_, "Heap Memory Pool", addr, size);
	assert(r == TX_SUCCESS);

	// Signal to any threads waiting on do_malloc that we are done
	initialized_ = true;
}

void* malloc(size_t size)
{
	void* ptr = NULL;

	/**
	* Since multiple threads could be racing to malloc, if we lost the race
	* we need to make sure the ThreadX pool has been created before we
	* try to allocate memory, or there will be an error
	*/
	while(!initialized_)
	{
		tx_thread_sleep(1);
	}

	if(size > 0)
	{
		// We simply wrap the threadX call into a standard form
		uint8_t r = tx_byte_allocate(&malloc_pool_, &ptr, size, TX_WAIT_FOREVER);

		// I add the string to provide a more helpful error output.  It's value is always true.
		assert(r == TX_SUCCESS && "malloc failed");
	} // else NULL if there was an error

	return ptr;
}

void free(void* ptr)
{
	// free should NEVER be called before malloc is init'd
	assert(initialized_);

	if(ptr)
	{
		// We simply wrap the threadX call into a standard form
		uint8_t r = tx_byte_release(ptr);
		ptr = NULL;
		assert(r == TX_SUCCESS);
	}
}
