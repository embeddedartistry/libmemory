/*
 * Copyright © 2022 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include <support/memory.h>
#include <tests.h>

// CMocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

int main(void)
{
	int overall_result = 0;

	// Generate JUnit results
	cmocka_set_message_output(CM_OUTPUT_XML);

	/*
	 * For this test framework, we need to allocate a block of memory before
	 * we run cmocka commands, otherwise they will fail since malloc cannot
	 * allocate anything
	 */
	allocate_memory();

	overall_result |= malloc_tests();

	return overall_result;
}
