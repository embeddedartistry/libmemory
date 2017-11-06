/*
* Copyright © 2017 Embedded Artistry LLC.
* License: MIT. See LICENSE file for details.
*/

#ifndef ALIGNED_MALLOC_H_
#define ALIGNED_MALLOC_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief Allocated aligned memory
*
* Allocate memory with at least alignment `align` and size `size`
* 	Memory which has been allocated with aligned_malloc() must be freed by calling
*	aligned_free(). Calling free() will result in a panic or other negative effects.
*
* @param align Alignment of the memory block.
*	Alignment refers to the starting address of the memory block.
*	If 32-byte alignment is requested, the start address of the returned pointer
*	will be 32-byte aligned.
*	Note: Alignment must be a power of two. (1, 2, 4, 8, etc.)
*
* @param size Size of the memory allocation
*
* @return Pointer to allocated memory. If memory was not successfully allocated,
*	the function will return NULL. This can happen due to invalid input
*	(alignment is 0, size is 0, alignment is not a power of 2) or due to insufficient
*	memory left for the requested allocation.
*/
void* aligned_malloc(size_t align, size_t size);

/**
* @brief A convenience macro for the Linux API
*
* memalign() is simply a convenience definition which provides the commonly-used
*	 Linux API memalign. This forwards the arguments to aligned_malloc() and behaves
*	 in the same manner.
*
* @param align Alignment of the memory block.
*	Alignment refers to the starting address of the memory block.
*	If 32-byte alignment is requested, the start address of the returned pointer
*	will be 32-byte aligned.
*	Note: Alignment must be a power of two. (1, 2, 4, 8, etc.)
*
* @param size Size of the memory allocation
*
* @return Pointer to allocated memory. If memory was not successfully allocated,
*	the function will return NULL. This can happen due to invalid input
*	(alignment is 0, size is 0, alignment is not a power of 2) or due to insufficient
*	memory left for the requested allocation.
*/
#define memalign(align, size) aligned_malloc(align, size)

/**
* @brief Free aligned memory
*
* Free memory that was allocated using aligned_malloc().
* 	This function *must not* be called on memory which was not allocated
* 	with aligned_malloc().
*
* @param ptr Pointer to the aligned_memory() block that will be freed.
*/
void aligned_free(void* ptr);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ALIGNED_MALLOC_H_
