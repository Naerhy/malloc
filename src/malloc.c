#include "libft_malloc.h"

zone_t* heap_g = NULL;
pthread_mutex_t mutex_g = PTHREAD_MUTEX_INITIALIZER;

static size_t align_size(size_t x, size_t align)
{
	return (x - 1) / align * align + align;
}

static int get_type_size(size_t size)
{
	if (size <= TINY_BLOCK_MAXSIZE)
		return 1;
	else if (size <= SMALL_BLOCK_MAXSIZE)
		return 2;
	else
		return 3;
}

static size_t get_zone_size_alloc(int type, size_t size)
{
	if (type == 1)
		return TINY_ZONE_SIZE;
	else if (type == 2)
		return SMALL_ZONE_SIZE;
	else
		return align_size(size + METADATA_ZONE_SIZE + METADATA_BLOCK_SIZE, 4096);
}

static void* alloc_new_zone(int type, size_t zone_size, size_t block_size)
{
	zone_t* new_zone;
	block_t* new_block;

	if (!check_max_zones())
		return NULL;
	new_zone = init_zone(type, zone_size);
	if (!new_zone)
		return NULL;
	new_block = (block_t*)(new_zone + 1);
	init_block(new_zone, new_block, block_size, NULL);
	return (void*)(new_block + 1);
}

void* malloc(size_t size)
{
	void* new_zone;
	void* available_space;
	int type;

	if (!size || !check_max_size(size))
		return NULL;
	size = align_size(size, 16);
	type = get_type_size(size);
	pthread_mutex_lock(&mutex_g);
	available_space = alloc_available_space(heap_g, size + METADATA_BLOCK_SIZE, type);
	if (available_space)
	{
		pthread_mutex_unlock(&mutex_g);
		return available_space;
	}
	new_zone = alloc_new_zone(type, get_zone_size_alloc(type, size), size + METADATA_BLOCK_SIZE);
	pthread_mutex_unlock(&mutex_g);
	return new_zone;
}
