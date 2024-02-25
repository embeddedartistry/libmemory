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

// We need to declare this prototype here since we don't include the header.
void* aligned_alloc(size_t align, size_t size);

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

#if(defined(__ISO_C_VISIBLE) && __ISO_C_VISIBLE >= 2011) || \
	(defined(__ISO_C_VISIBLE) && __STDC_VERSION >= 20112L)
void* aligned_alloc(size_t align, size_t size)
{
	return aligned_malloc(align, size);
}
#endif

/**
 * This function is kept for compatibility and it simply calls free().
 */
void aligned_free(void* ptr) { free(ptr); }
