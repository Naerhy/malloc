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

size_t get_remaining_space(zone_t const* zone)
{
	block_t* last_block;
	char* start;
	char* end;

	last_block = get_last_block((block_t*)(zone + 1));
	start = (char*)(last_block + 1) + last_block->size;
	end = (char*)(zone + 1) + zone->size;
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
			total += block->size;
			block = block->next;
		}
		zone = zone->next;
	}
	return total;
}

size_t get_nb_zones(zone_t* zone)
{
	size_t nb;

	nb = 0;
	while (zone)
	{
		nb++;
		zone = zone->next;
	}
	return nb;
}
