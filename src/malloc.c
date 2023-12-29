#include "libft_malloc.h"

void* heap_g = NULL;

static zone_t* alloc_zone(int type, size_t zone_size, size_t block_size)
{
	zone_t* new_zone;

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

void* temp_malloc(size_t size)
{
	zone_t* new_zone;
	block_t* existing_block;
	int type;

	if (!size)
		return NULL;
	size = get_next_mult(size, 8);
	if (size > SMALL_BLOCK_MAXSIZE)
	{
		new_zone = alloc_zone(3, size + METADATA_ZONE_SIZE + METADATA_BLOCK_SIZE, size);
		return (!new_zone) ? NULL : (void*)((block_t*)(new_zone + 1) + 1);
	}
	else
	{
		type = (size <= TINY_BLOCK_MAXSIZE) ? 1 : 2;
		existing_block = first_fit(size, type);
		if (existing_block)
			return (void*)(existing_block + 1);
		else
		{
			new_zone = alloc_zone(type, (type == 1) ? TINY_ZONE_SIZE : SMALL_ZONE_SIZE, size);
			return (!new_zone) ? NULL : (void*)((block_t*)(new_zone + 1) + 1);
		}
	}
}
