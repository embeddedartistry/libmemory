/*
* Copyright © 2018 Embedded Artistry LLC.
* License: MIT. See LICENSE file for details.
*/

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#pragma mark - Declarations -

/** FreeRTOS internal memory pool stucture when using heap_5.c
*
* Allocates two blocks of RAM for use by the heap.
*	The first is a block of 0x10000 bytes starting from address 0x80000000
*	The second is left open to demonstrate configuration with malloc_addblock
*
* The block with the lowest starting address should appear first in the array
*/
static HeapRegion_t heap_regions[] =
{
    { ( uint8_t * ) 0x80000000UL, 0x10000 }, //Fixed definition
    { NULL, 0 }, // Will be updated by malloc_addblock
    { NULL, 0 } // NULL terminate
};

/*
* Flag that is used in do_malloc() to cause competing threads to wait until
* initialization is completed before allocating memory.
*/
volatile static bool initialized_ = false;

#pragma mark - Private Functions -

/**
 * malloc_addblock must be called before memory allocation calls are made.
 * In this FreeRTOS implementation, malloc() calls will block until memory
 * has been allocated
 */
void malloc_addblock(void* addr, size_t size)
{
	assert(addr && (size > 0));

	if((uintptr_t)addr > (uintptr_t) heap_regions[0].pucStartAddress)
	{
		// Address is greater than the pre-allocated address - all ok
		heap_regions[1].pucStartAddress = (uint8_t*) addr;
		heap_regions[1].xSizeInBytes = size;
	}
	else
	{
		// Set the old block to the second slot
		heap_regions[1].pucStartAddress = heap_regions[0].pucStartAddress
		heap_regions[1].xSizeInBytes = heap_regions[0].xSizeInBytes;

		// Now set the new block
		heap_regions[0].pucStartAddress = (uint8_t*) addr;
		heap_regions[0].xSizeInBytes = size;
	}

	// Pass the array into vPortDefineHeapRegions() to enable malloc()
	vPortDefineHeapRegions(heap_regions);

	// Signal to any waiting threads that we are done initializing
	initialized_ = true;
}

void* malloc(size_t size)
{
	void* ptr = NULL;

	while(!initialized_)
	{
		// Thread blocks until application malloc has been correctly initialized
		vTaskDelay(1);
	}

	if(size > 0)
	{
		// We simply wrap the FreeRTOS call into a standard form
		ptr = pvPortMalloc(size);
	} // else NULL if there was an error

	return ptr;
}

void free(void* ptr)
{
	/// free should NEVER be called before malloc is init'd
	assert(initialized_);

	if(ptr)
	{
		// We simply wrap the FreeRTOS call into a standard form
		vPortFree(ptr);
	}
}
