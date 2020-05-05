/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include <malloc.h>
#include <support/memory.h>

#define MEM_BLOCK_SIZE (1024 * 1024)

static volatile bool allocated = false;
static const size_t memblock_size = MEM_BLOCK_SIZE;
static uint8_t mem_block[MEM_BLOCK_SIZE];
static const uintptr_t mem_block_addr = (uintptr_t)mem_block;

void allocate_memory()
{
	if(!allocated)
	{
		malloc_addblock(mem_block, memblock_size);
		allocated = true;
	}
}

bool memory_allocated()
{
	return allocated;
}

uintptr_t block_start_addr()
{
	return mem_block_addr;
}

uintptr_t block_end_addr()
{
	return mem_block_addr + MEM_BLOCK_SIZE;
}

size_t block_size()
{
	return memblock_size;
}
