#ifndef LIBFT_MALLOC_H
#define LIBFT_MALLOC_H

#include <sys/mman.h>
#include <unistd.h>

typedef struct zone_s
{
	int type;
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

#define METADATA_ZONE_SIZE sizeof(zone_t)
#define METADATA_BLOCK_SIZE sizeof(block_t)
#define TINY_ZONE_SIZE (getpagesize() * 4)
#define TINY_BLOCK_MAXSIZE ((TINY_ZONE_SIZE - METADATA_ZONE_SIZE - (METADATA_BLOCK_SIZE * 100)) / 100)
#define SMALL_ZONE_SIZE (getpagesize() * 16)
#define SMALL_BLOCK_MAXSIZE ((SMALL_ZONE_SIZE - METADATA_ZONE_SIZE - (METADATA_BLOCK_SIZE * 100)) / 100)

extern void* heap_g;

void* malloc(size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);
void show_alloc_mem(void);

size_t get_next_mult(size_t x, size_t mult);
zone_t* init_zone(int type, size_t size);
void init_block(zone_t* zone, block_t* block, size_t size, block_t* previous_block);
block_t* first_fit(size_t size, int type);
size_t get_remaining_space(zone_t const* zone);
zone_t* get_last_zone(zone_t* zone);
block_t* get_first_block(block_t* block);
block_t* get_last_block(block_t* block);
size_t get_total_size(zone_t* zone);
void* cst_memcpy(void* dest, void const* src, size_t n);
void write_str(char const* str);
void write_nb(size_t nb);
void write_ptr(unsigned long nb);

#endif
