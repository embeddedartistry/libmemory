/*
 * Copyright © 2021 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include <assert.h>
#include <malloc.h>
#include <memory.h>
#include <stdio.h>

__attribute__((weak)) void malloc_addblock(void* addr, size_t size)
{
	(void)addr;
	(void)size;
	assert(0); // malloc_addblock is not supported in this implementation
	printf("Malloc_addblock is not supported in this implementation\n");
}

__attribute__((weak)) void malloc_init(void)
{
	assert(0); // malloc_addblock is not supported in this implementation
	printf("malloc_init is not supported in this implementation\n");
}
