/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include <malloc.h>
#include <stdint.h>
#include <support/memory.h>
#include <tests.h>

// CMocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

#define ALLOCATION_TEST_COUNT 768

static void* p[ALLOCATION_TEST_COUNT];

static void malloc_test(void** __attribute__((unused)) state)
{
	// Make sure memory was previously allocated
	if(!memory_allocated())
	{
		allocate_memory();
	}

	assert_true(memory_allocated());

	uintptr_t mem_block_addr = block_start_addr();
	uintptr_t mem_block_end_addr = block_end_addr();
	size_t mem_block_size = block_size();

	void* ptr = malloc(1024);

	assert_non_null(ptr);
	assert_in_range((uintptr_t)ptr, mem_block_addr, mem_block_end_addr);

	free(ptr);

	// Check request too large
	ptr = malloc(2 * mem_block_size);
	assert_null(ptr);

	for(int i = 0; i < ALLOCATION_TEST_COUNT; i++)
	{
		p[i] = malloc(1024);
		assert_non_null(p[i]);
		assert_in_range((uintptr_t)p[i], mem_block_addr, mem_block_end_addr);
	}

	// Cleanup
	for(int i = 0; i < ALLOCATION_TEST_COUNT; i++)
	{
		free(p[i]);
	}

	// Run test again, will not fail if our memory has been returned!
	for(int i = 0; i < ALLOCATION_TEST_COUNT; i++)
	{
		p[i] = malloc(1024);
		assert_non_null(p[i]);
		assert_in_range((uintptr_t)p[i], mem_block_addr, mem_block_end_addr);
	}

	// Cleanup
	for(int i = 0; i < ALLOCATION_TEST_COUNT; i++)
	{
		free(p[i]);
	}
}

int malloc_tests(void)
{
	const struct CMUnitTest malloc_test_suite[] = {cmocka_unit_test(malloc_test)};

	return cmocka_run_group_tests(malloc_test_suite, NULL, NULL);
}
