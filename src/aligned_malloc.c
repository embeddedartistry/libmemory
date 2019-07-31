/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include "aligned_malloc.h"

#pragma mark - Definitions -

// We forward declare these to prevent include header prevention from the OS
extern void* malloc(size_t size);
extern void free(void* ptr);

/**
 * Simple macro for making sure memory addresses are aligned
 * to the nearest power of two
 */
#ifndef align_up
#define align_up(num, align) (((num) + ((align)-1)) & ~((align)-1))
#endif

/// Number of bytes we're using for storing the aligned pointer offset
typedef uint16_t offset_t;

/// Macro for accessing the size of our current pointer offset
#define PTR_OFFSET_SZ sizeof(offset_t)

#pragma mark - APIs -

/**
 * We will call malloc with extra bytes for our header and the offset
 *	required to guarantee the desired alignment.
 */
void* aligned_malloc(size_t align, size_t size)
{
	void* ptr = NULL;

	// We want it to be a power of two since align_up operates on powers of two
	assert((align & (align - 1)) == 0);

	if(align && size)
	{
		/*
		 * We know we have to fit an offset value
		 * We also allocate extra bytes to ensure we can meet the alignment
		 */
		size_t hdr_size = PTR_OFFSET_SZ + (align - 1);
		void* p = malloc(size + hdr_size);

		if(p)
		{
			/*
			 * Add the offset size to malloc's pointer (we will always store that)
			 * Then align the resulting value to the arget alignment
			 */
			ptr = (void*)align_up(((uintptr_t)p + PTR_OFFSET_SZ), align);

			// Calculate the offset and store it behind our aligned pointer
			*((offset_t*)ptr - 1) = (offset_t)((uintptr_t)ptr - (uintptr_t)p);

		} // else NULL, could not malloc
	} // else NULL, invalid arguments

	return ptr;
}

#if(defined(__ISO_C_VISIBLE) && __ISO_C_VISIBLE >= 2011) || \
	(defined(__ISO_C_VISIBLE) && __STDC_VERSION >= 20112L)
void* aligned_alloc(size_t align, size_t size)
{
	return aligned_malloc(align, size);
}
#endif

/**
 * aligned_free works like free(), but we work backwards from the returned
 * pointer to find the correct offset and pointer location to return to free()
 * Note that it is VERY BAD to call free() on an aligned_malloc() pointer.
 */
void aligned_free(void* ptr)
{
	assert(ptr);

	/*
	 * Walk backwards from the passed-in pointer to get the pointer offset
	 * We convert to an offset_t pointer and rely on pointer math to get the data
	 */
	offset_t offset = *((offset_t*)ptr - 1);

	/*
	 * Once we have the offset, we can get our original pointer and call free
	 */
	void* p = (void*)((uint8_t*)ptr - offset);
	free(p);
}
