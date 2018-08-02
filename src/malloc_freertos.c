/*
 * Copyright © 2018 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include <assert.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>

/**
 * NOTE: This FreeRTOS malloc implementation requires heap_5.c
 *
 * Please define the correct heap_region for your project.
 */

#pragma mark - Definitions

/**
 * Your application can define this macro to increase the
 */
#ifndef FREERTOS_HEAP_REGION_CNT
#define FREERTOS_HEAP_REGION_CNT 2
#endif

#pragma mark - Declarations -

/// Maximum number of heap regions that can be specified
static const uint8_t heap_region_max = FREERTOS_HEAP_REGION_CNT;

/// Current number of allocated heap regions
static volatile uint8_t heap_region_cnt = 0;

/**
 * FreeRTOS internal memory pool stucture when using heap_5.c
 *
 * The block with the lowest starting address should appear first in the array
 *
 * An additional block is allocated to serve as a NULL terminator
 */
static HeapRegion_t heap_regions[FREERTOS_HEAP_REGION_CNT + 1];

/**
 * Flag that is used in malloc() to cause competing threads to wait until
 * initialization is completed before allocating memory.
 */
volatile static bool initialized_ = false;

#pragma mark - Private Functions -

static int cmp_heap(const void* a, const void* b)
{
	const HeapRegion_t *ua = a, *ub = b;

	return ((ua->pucStartAddress < ub->pucStartAddress)
				? -1
				: ((ua->pucStartAddress != ub->pucStartAddress)));
}

/**
 * malloc_addblock must be called before memory allocation calls are made.
 * In this FreeRTOS implementation, malloc() calls will block until memory
 * has been allocated
 */
void malloc_addblock(void* addr, size_t size)
{
	assert(addr && (size > 0));
	assert((heap_region_cnt < heap_region_max) && "Too many heap regions!");

	// Increment the count early to claim a spot in case of multi-threads
	uint8_t cnt = heap_region_cnt++;

	if(cnt < heap_region_max)
	{
		// We have space - add it to the table
		heap_regions[cnt].pucStartAddress = (uint8_t*)addr;
		heap_regions[cnt].xSizeInBytes = size;
	}
	else
	{
		// Decrement the count if we don't have space
		heap_region_cnt--;
	}
}

__attribute__((weak)) void malloc_init()
{
	assert((heap_region_cnt > 0) && !initialized_);

	if(heap_region_cnt > 0 && !initialized_)
	{
		// Sort the heap regions so addresses are in the correct order
		qsort(heap_regions, heap_region_cnt, sizeof(HeapRegion_t), cmp_heap);

		// Pass the array into vPortDefineHeapRegions() to enable malloc()
		vPortDefineHeapRegions(heap_regions);

		// Signal to any waiting threads that we are done initializing
		initialized_ = true;
	}
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
