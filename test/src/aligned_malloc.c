/*
* Copyright © 2017 Embedded Artistry LLC.
* License: MIT. See LICENSE file for details.
*/

#include <aligned_malloc.h>
#include <support/memory.h>

// CMocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka/cmocka.h>
// clang-format on

static void aligned_malloc_test(void** state)
{
	// Make sure memory was previously allocated
	if(!memory_allocated())
	{
		allocate_memory();
	}

	assert_true(memory_allocated());

	intptr_t mem_block_addr = block_start_addr();
	intptr_t mem_block_end_addr = block_end_addr();
	size_t mem_block_size = block_size();

	size_t align = 2;

	for(size_t align = 2; align <= 8192; align *= 2)
	{
		void* ptr = aligned_malloc(align, 32);
		assert_non_null(ptr);
		assert_in_range((intptr_t)ptr, mem_block_addr, mem_block_end_addr);
		assert_false(((uintptr_t)ptr) & (align - 1));
		aligned_free(ptr);
	}

	// Run again, make sure malloc does not fail and memory was really freed
	for(size_t align = 2; align <= 8192; align *= 2)
	{
		void* ptr = aligned_malloc(align, 32);
		assert_non_null(ptr);
		assert_in_range((intptr_t)ptr, mem_block_addr, mem_block_end_addr);
		assert_false(((uintptr_t)ptr) & (align - 1));
		aligned_free(ptr);
	}

	// We can have one byte alignment - check
	void* ptr = aligned_malloc(1, 1024);
	assert_non_null(ptr);

	// Check large allocation
	ptr = aligned_malloc(32, mem_block_size * 2);
	assert_null(ptr);

	// Check bad input
	ptr = aligned_malloc(0, 1024);
	assert_null(ptr);
}

int aligned_malloc_tests(void)
{
	const struct CMUnitTest aligned_malloc_tests[] = {cmocka_unit_test(aligned_malloc_test)};

	return cmocka_run_group_tests(aligned_malloc_tests, NULL, NULL);
}
