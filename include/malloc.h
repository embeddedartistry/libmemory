/*
* Copyright © 2017 Embedded Artistry LLC.
* License: MIT. See LICENSE file for details.
*/

#ifndef __MALLOC_H_
#define __MALLOC_H_

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#include <stdlib.h>

/**
* Initialize malloc with a memory address and pool size
*/
void malloc_addblock(void *addr, size_t size);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__MALLOC_H_
