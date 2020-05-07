/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#ifndef MEMORY_SUPPORT_H_
#define MEMORY_SUPPORT_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

void allocate_memory(void);
uintptr_t block_start_addr(void);
size_t block_size(void);
uintptr_t block_end_addr(void);
bool memory_allocated(void);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // MEMORY_SUPPORT_H_
