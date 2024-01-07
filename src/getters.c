#include "libft_malloc.h"

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
	while (block->previous)
		block = block->previous;
	return block;
}

block_t* get_last_block(block_t* block)
{
	while (block->next)
		block = block->next;
	return block;
}

size_t get_available_space(zone_t const* zone)
{
	block_t* last_block;
	unsigned char* start;
	unsigned char* end;

	last_block = get_last_block((block_t*)(zone + 1));
	start = (unsigned char*)last_block + last_block->size;
	end = (unsigned char*)zone + zone->size;
	return end - start;
}

size_t get_total_size(zone_t* zone)
{
	block_t* block;
	size_t total;

	total = 0;
	while (zone)
	{
		block = (block_t*)(zone + 1);
		while (block)
		{
			total += block->size - METADATA_BLOCK_SIZE;
			block = block->next;
		}
		zone = zone->next;
	}
	return total;
}
