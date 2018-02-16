/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include <malloc.h>
#include <support/memory.h>

static volatile bool allocated = false;
static const size_t memblock_size = (1024 * 1024);
static uint8_t mem_block[memblock_size];
static const intptr_t mem_block_addr = (intptr_t)mem_block;
static const intptr_t mem_block_addr_end = mem_block_addr + memblock_size;

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

intptr_t block_start_addr()
{
	return mem_block_addr;
}

intptr_t block_end_addr()
{
	return mem_block_addr_end;
}

size_t block_size()
{
	return memblock_size;
}
