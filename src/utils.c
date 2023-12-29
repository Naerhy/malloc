#include "libft_malloc.h"

size_t get_next_mult(size_t x, size_t mult)
{
	return (x - 1) / mult * mult + mult;
}

zone_t* init_zone(int type, size_t size)
{
	zone_t* zone;

	zone = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (zone == MAP_FAILED)
		return NULL;
	zone->type = type;
	zone->size = size - METADATA_ZONE_SIZE;
	zone->free_size = zone->size;
	zone->previous = get_last_zone(heap_g);
	zone->next = NULL;
	return zone;
}

void init_block(zone_t* zone, block_t* block, size_t size, block_t* previous)
{
	block->size = size;
	block->is_free = 0;
	block->previous = previous;
	block->next = NULL;
	if (previous)
		previous->next = block;
	zone->free_size -= size + METADATA_BLOCK_SIZE;
}

block_t* first_fit(size_t size, int type)
{
	zone_t* zone;
	block_t* block;
	block_t* last_block;

	zone = heap_g;
	while (zone)
	{
		if (zone->type == type && zone->free_size >= size + METADATA_BLOCK_SIZE)
		{
			block = (block_t*)(zone + 1);
			while (block)
			{
				if (block->is_free && block->size >= size)
				{
					block->is_free = 0;
					zone->free_size -= size + METADATA_BLOCK_SIZE;
					return block;
				}
				block = block->next;
			}
			if (get_remaining_space(zone) >= size + METADATA_BLOCK_SIZE)
			{
				last_block = get_last_block((block_t*)(zone + 1));
				init_block(zone, (block_t*)((char*)(last_block + 1) + last_block->size),
						size, last_block);
				return (block_t*)((char*)(last_block + 1) + last_block->size);
			}
		}
		zone = zone->next;
	}
	return NULL;
}

size_t get_remaining_space(zone_t* zone)
{
	block_t* last_block;
	char* start;
	char* end;

	last_block = get_last_block((block_t*)(zone + 1));
	start = (char*)(last_block + 1) + last_block->size;
	end = (char*)(zone + 1) + zone->size;
	return end - start;
}

zone_t* get_last_zone(zone_t* zone)
{
	if (!zone)
		return NULL;
	while (zone->next)
		zone = zone->next;
	return zone;
}

block_t* get_first_block(block_t* block)
{
	if (!block)
		return NULL;
	while (block->previous)
		block = block->previous;
	return block;
}

block_t* get_last_block(block_t* block)
{
	if (!block)
		return NULL;
	while (block->next)
		block = block->next;
	return block;
}
