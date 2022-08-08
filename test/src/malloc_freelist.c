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

static void* pointer_array[ALLOCATION_TEST_COUNT];

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

	for(size_t i = 0; i < ALLOCATION_TEST_COUNT; i++)
	{
		pointer_array[i] = malloc(1024);
		assert_non_null(pointer_array[i]);
		assert_in_range((uintptr_t)pointer_array[i], mem_block_addr, mem_block_end_addr);
		// Test for unique addresses
		if(i > 0)
		{
			assert_not_in_set((uintptr_t)pointer_array[i], (uintptr_t*)pointer_array, i - 1);
		}
	}

	// Cleanup
	for(size_t i = 0; i < ALLOCATION_TEST_COUNT; i++)
	{
		free(pointer_array[i]);
	}

	// Run test again, will not fail if our memory has been returned!
	for(size_t i = 0; i < ALLOCATION_TEST_COUNT; i++)
	{
		pointer_array[i] = malloc(1024);
		assert_non_null(pointer_array[i]);
		assert_in_range((uintptr_t)pointer_array[i], mem_block_addr, mem_block_end_addr);
		if(i > 0)
		{
			assert_not_in_set((uintptr_t)pointer_array[i], (uintptr_t*)pointer_array, i - 1);
		}
	}

	// Cleanup
	for(size_t i = 0; i < ALLOCATION_TEST_COUNT; i++)
	{
		free(pointer_array[i]);
	}
}

int malloc_tests(void)
{
	const struct CMUnitTest malloc_test_suite[] = {cmocka_unit_test(malloc_test)};

	return cmocka_run_group_tests(malloc_test_suite, NULL, NULL);
}
