/*
* Copyright © 2017 Embedded Artistry LLC.
* License: MIT. See LICENSE file for details.
*/

#ifndef ALIGNED_MALLOC_H_
#define ALIGNED_MALLOC_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
* Allocate memory with at least alignment `align` and size `size`
* Must be freed by calling aligned_free!
*/
void * aligned_malloc(size_t align, size_t size);

//Convenience macro for memalign, the linux API
#define memalign(align, size) aligned_malloc(align, size)

/**
* Free memory that was allocated using aligned_malloc
*/
void aligned_free(void * ptr);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //ALIGNED_MALLOC_H_
