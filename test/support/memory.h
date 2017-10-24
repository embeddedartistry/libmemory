/*
* Copyright © 2017 Embedded Artistry LLC.
* License: MIT. See LICENSE file for details.
*/

#ifndef MEMORY_SUPPORT_H_
#define MEMORY_SUPPORT_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

void allocate_memory();
intptr_t block_start_addr();
size_t block_size();
intptr_t block_end_addr();
bool memory_allocated();

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //MEMORY_SUPPORT_H_
