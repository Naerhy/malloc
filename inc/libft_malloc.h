#ifndef __LIBFT_MALLOC_H__
#define __LIBFT_MALLOC_H__

#include <stdlib.h>

void* malloc(size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);

void show_alloc_mem(void);

#endif
