/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include <aligned_malloc.h>
#include <errno.h>
#include <support/memory.h>
#include <tests.h>

// CMocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

static void aligned_malloc_test(void** __attribute__((unused)) state)
{
	// Make sure memory was previously allocated
	if(!memory_allocated())
	{
		allocate_memory();
	}

	assert_true(memory_allocated());

	uintptr_t mem_block_addr = block_start_addr();
	uintptr_t mem_block_end_addr = block_end_addr();
#ifdef ALIGNED_MALLOC_CHECK_LARGE_ALLOC
	size_t mem_block_size = block_size();
#endif

	for(size_t align = 2; align <= 8192; align *= 2)
	{
		void* ptr = aligned_malloc(align, 32);
		assert_non_null(ptr);
		assert_in_range((uintptr_t)ptr, mem_block_addr, mem_block_end_addr);
		assert_false(((uintptr_t)ptr) & (align - 1));
		aligned_free(ptr);
	}

	// Run again, make sure malloc does not fail and memory was really freed
	for(size_t align = 2; align <= 8192; align *= 2)
	{
		void* ptr = aligned_malloc(align, 32);
		assert_non_null(ptr);
		assert_in_range((uintptr_t)ptr, mem_block_addr, mem_block_end_addr);
		assert_false(((uintptr_t)ptr) & (align - 1));
		aligned_free(ptr);
	}

	// We can have one byte alignment - check
	void* ptr = aligned_malloc(1, 1024);
	assert_non_null(ptr);
	aligned_free(ptr);

#ifdef ALIGNED_MALLOC_CHECK_LARGE_ALLOC
	// Check large allocation
	ptr = aligned_malloc(32, mem_block_size * 2);
	assert_null(ptr);
#endif

	// Check bad input
	ptr = aligned_malloc(0, 1024);
	assert_null(ptr);
}

// Might be unused in the case that AddressSanitizer is enabled
__attribute__((unused)) static void posix_memalign_test(void** __attribute__((unused)) state)
{
	void* ptr = NULL;
	int return_code = posix_memalign(&ptr, 8, 8);
	assert_non_null(ptr);
	assert_int_equal(return_code, 0);

	aligned_free(ptr);
	ptr = NULL;

	return_code = posix_memalign(&ptr, 3, 8);
	assert_null(ptr);
	assert_int_equal(return_code, EINVAL);
}

int aligned_malloc_tests(void)
{
	const struct CMUnitTest aligned_malloc_tests[] = {
		cmocka_unit_test(aligned_malloc_test),
	// POSIX Memalign tests have problems with address sanitizer b/c it replaces our memalign
	// with their memalign, but we call aligned free.. triggering a failure.
#if !defined(__SANITIZE_ADDRESS__)
#if defined(__has_feature)
#if !__has_feature(address_sanitizer)
		cmocka_unit_test(posix_memalign_test),
#endif
#else // no __has_feature, trust __SANITIZE_ADDRESS__
		cmocka_unit_test(posix_memalign_test),
#endif
#endif
	};

	return cmocka_run_group_tests(aligned_malloc_tests, NULL, NULL);
}
