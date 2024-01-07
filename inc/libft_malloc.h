#ifndef LIBFT_MALLOC_H
#define LIBFT_MALLOC_H

#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct zone_s
{
	int type;
	size_t size;
	size_t free_size;
	struct zone_s* previous;
	struct zone_s* next;
	size_t padding;
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
#define TINY_ZONE_SIZE (getpagesize() * 16)
#define TINY_BLOCK_MAXSIZE ((TINY_ZONE_SIZE - METADATA_ZONE_SIZE - (METADATA_BLOCK_SIZE * 100)) / 100)
#define SMALL_ZONE_SIZE (getpagesize() * 48)
#define SMALL_BLOCK_MAXSIZE ((SMALL_ZONE_SIZE - METADATA_ZONE_SIZE - (METADATA_BLOCK_SIZE * 100)) / 100)

extern zone_t* heap_g;
extern pthread_mutex_t mutex_g;

void* malloc(size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);
void show_alloc_mem(void);
void show_alloc_mem_ex(void);

zone_t* init_zone(int type, size_t size);
void init_block(zone_t* zone, block_t* block, size_t size, block_t* previous_block);
void* alloc_available_space(zone_t* zone, size_t size, int type);
int valid_ptr(zone_t* zone, void* ptr);
int check_max_zones(void);
int check_max_size(size_t size);

zone_t* get_last_zone(zone_t* zone);
block_t* get_first_block(block_t* block);
block_t* get_last_block(block_t* block);
size_t get_available_space(zone_t const* zone);
size_t get_total_size(zone_t* zone);

size_t cst_atoi(char const* str);
void* cst_memcpy(void* dest, void const* src, size_t n);
size_t cst_strlen(char const* str);

void write_str(char const* str);
void write_nb(char const* before, size_t nb, char const* after);
void write_hex(char const* before, unsigned long nb, int is_address, char const* after);

#endif
