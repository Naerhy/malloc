#include "libft_malloc.h"

void* heap_g = NULL;
pthread_mutex_t mutex_g = PTHREAD_MUTEX_INITIALIZER;

static zone_t* alloc_zone(int type, size_t zone_size, size_t block_size)
{
	zone_t* new_zone;

	if (!check_max_zones())
		return NULL;
	new_zone = init_zone(type, zone_size);
	if (!new_zone)
		return NULL;
	init_block(new_zone, (block_t*)(new_zone + 1), block_size, NULL);
	if (!heap_g)
		heap_g = (void*)new_zone;
	else
		(get_last_zone(heap_g))->next = new_zone;
	return new_zone;
}

void* malloc(size_t size)
{
	zone_t* new_zone;
	block_t* existing_block;
	int type;

	if (!size)
		return NULL;
	if (!check_max_size(size))
		return NULL;
	size = align_size(size, 16);
	pthread_mutex_lock(&mutex_g);
	if (size > SMALL_BLOCK_MAXSIZE)
	{
		new_zone = alloc_zone(3, size + METADATA_ZONE_SIZE + METADATA_BLOCK_SIZE, size);
		pthread_mutex_unlock(&mutex_g);
		return (new_zone) ? (void*)((block_t*)(new_zone + 1) + 1) : NULL;
	}
	else
	{
		type = (size <= TINY_BLOCK_MAXSIZE) ? 1 : 2;
		existing_block = first_fit(size, type);
		if (existing_block)
		{
			pthread_mutex_unlock(&mutex_g);
			return (void*)(existing_block + 1);
		}
		else
		{
			new_zone = alloc_zone(type, (type == 1) ? TINY_ZONE_SIZE : SMALL_ZONE_SIZE, size);
			pthread_mutex_unlock(&mutex_g);
			return (new_zone) ? (void*)((block_t*)(new_zone + 1) + 1) : NULL;
		}
	}
}
