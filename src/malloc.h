#ifndef __MALLOC_H_
#define __MALLOC_H_

#include "malloc_freelist.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

void * malloc(size_t size);
void free(void * ptr);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__MALLOC_H_
