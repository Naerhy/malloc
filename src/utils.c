#include "libft_malloc.h"

zone_t* init_zone(int type, size_t size)
{
	zone_t* zone;

	zone = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (zone == MAP_FAILED)
		return NULL;
	zone->type = type;
	zone->size = size;
	zone->free_size = zone->size - METADATA_ZONE_SIZE;
	zone->previous = get_last_zone(heap_g);
	if (zone->previous)
		zone->previous->next = zone;
	else
		heap_g = zone;
	zone->next = NULL;
	return zone;
}

void init_block(zone_t* zone, block_t* block, size_t size, block_t* previous)
{
	block->size = size;
	block->is_free = 0;
	block->previous = previous;
	if (block->previous)
		previous->next = block;
	block->next = NULL;
	zone->free_size -= block->size;
}

void* alloc_available_space(zone_t* zone, size_t size, int type)
{
	block_t* block;
	block_t* last_block;
	block_t* new_block;

	if (type == 3)
		return NULL;
	while (zone)
	{
		if (zone->type == type && size <= zone->free_size)
		{
			block = (block_t*)(zone + 1);
			while (block)
			{
				if (block->is_free && size <= block->size)
				{
					block->is_free = 0;
					zone->free_size -= block->size;
					return (void*)(block + 1);
				}
				block = block->next;
			}
			if (size <= get_available_space(zone))
			{
				last_block = get_last_block((block_t*)(zone + 1));
				new_block = (block_t*)((unsigned char*)last_block + last_block->size);
				init_block(zone, new_block, size, last_block);
				return (void*)(new_block + 1);
			}
		}
		zone = zone->next;
	}
	return NULL;
}

int valid_ptr(zone_t* zone, void* ptr)
{
	block_t* block;

	while (zone)
	{
		block = (block_t*)(zone + 1);
		while (block)
		{
			if (ptr == block + 1)
				return 1;
			block = block->next;
		}
		zone = zone->next;
	}
	return 0;
}
