/*
 * Copyright © 2019 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include <assert.h>
#include <malloc.h>
#include <memory.h>

#pragma mark - APIs -

__attribute__((weak)) void malloc_init(void)
{
	assert(0); // malloc is not supported.
}

__attribute__((weak)) void malloc_addblock(void* addr, size_t size)
{
	assert(0); // malloc is not supported.
}

void* malloc(size_t __attribute__((unused)) size)
{
	assert(0); // malloc is not supported
	return NULL;
}

void free(__attribute__((unused)) void* ptr)
{
	assert(0); // malloc is not supported
	while(1)
	{
		// Loop forever
	}
}
