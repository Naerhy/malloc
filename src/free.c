#include "libft_malloc.h"

static void release_memory(zone_t* zone)
{
	if (zone->previous)
		zone->previous->next = zone->next;
	else
		heap_g = zone->next;
	if (zone->next)
		zone->next->previous = zone->previous;
	munmap(zone, zone->size + METADATA_ZONE_SIZE);
}

// TODO: check if safe to free a block which is already is_free = 1
void temp_free(void* ptr)
{
	block_t* block;
	zone_t* zone;

	if (ptr)
	{
		block = (block_t*)ptr - 1;
		block->is_free = 1;
		if (block->previous)
			zone = (zone_t*)get_first_block(block) - 1;
		else
			zone = (zone_t*)block - 1;
		zone->free_size += block->size + METADATA_BLOCK_SIZE;
		if (zone->free_size == zone->size)
			release_memory(zone);
	}
}
