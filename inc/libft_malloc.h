#ifndef LIBFT_MALLOC_H
#define LIBFT_MALLOC_H

#include <stdlib.h>

typedef struct s_zone
{
	int type;
	size_t size;
	size_t free_size;
	// nb blocks => maybe useless because to check if empty we can compare
	// if size == free_size
} t_zone;

typedef struct s_block
{
	size_t size;
	int is_free;
} t_block;

void* malloc(size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);

void show_alloc_mem(void);

#endif
