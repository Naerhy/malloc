#ifndef LIBFT_MALLOC_H
#define LIBFT_MALLOC_H

// TODO check memory alignment
// TODO rename malloc function to definitive naming

#include <sys/mman.h>
#include <sys/resource.h>
#include <unistd.h>

typedef struct zone_s
{
	int type; // check if necessary
	size_t size;
	size_t free_size;
	struct zone_s* previous;
	struct zone_s* next;
} zone_t;

typedef struct block_s
{
	size_t size;
	int is_free;
	struct block_s* previous;
	struct block_s* next;
} block_t;

#define TINY_ZONE_SIZE (getpagesize() * 4)
#define TINY_BLOCK_MAX_SIZE ((TINY_ZONE_SIZE - sizeof(zone_t) - (sizeof(block_t) * 100)) / 100)

#define SMALL_ZONE_SIZE (getpagesize() * 16)
#define SMALL_BLOCK_MAX_SIZE ((SMALL_ZONE_SIZE - sizeof(zone_t) - (sizeof(block_t) * 100)) / 100)

#define MD_ZONE_SIZE sizeof(zone_t)
#define MD_BLOCK_SIZE sizeof(block_t)

extern void* heap_g;

void* temp_malloc(size_t size);
//void* realloc(void* ptr, size_t size);
//void free(void* ptr);

//void show_alloc_mem(void);

size_t align_size(size_t size);

#endif
