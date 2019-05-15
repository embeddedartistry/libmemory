/*
 * Copyright © 2019 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include <heap.hpp>
#include <malloc.h>

void malloc_addblock(void* addr, size_t size)
{
	os::Heap::addBlock(addr, size);
}

__attribute__((weak)) void malloc_init()
{
	os::Heap::init();
}

void* malloc(size_t size)
{
	return os::Heap::alloc(size);
}

void free(void* ptr)
{
	os::Heap::free(ptr);
}
