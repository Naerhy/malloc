#include "libft_malloc.h"

static int enough_size(size_t size, int type)
{
	if (type == 1)
		return size <= TINY_BLOCK_MAXSIZE;
	return size <= SMALL_BLOCK_MAXSIZE;
}

static void try_merge_blocks(block_t* first, block_t* second, int type)
{
	size_t combined_size;

	if (first && second && first->is_free && second->is_free)
	{
		combined_size = first->size + second->size + METADATA_BLOCK_SIZE;
		if (enough_size(combined_size, type))
		{
			first->size = combined_size;
			first->next = second->next;
			if (second->next)
				second->next->previous = first;
		}
	}
}

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

void free(void* ptr)
{
	block_t* block;
	zone_t* zone;

	if (ptr)
	{
		pthread_mutex_lock(&mutex_g);
		block = (block_t*)ptr - 1;
		block->is_free = 1;
		if (check_fill_block())
			fill_block(block);
		if (block->previous)
			zone = (zone_t*)get_first_block(block) - 1;
		else
			zone = (zone_t*)block - 1;
		zone->free_size += block->size + METADATA_BLOCK_SIZE;
		try_merge_blocks(block->previous, block, zone->type);
		try_merge_blocks(block, block->next, zone->type);
		if (zone->free_size == zone->size)
			release_memory(zone);
		pthread_mutex_unlock(&mutex_g);
	}
}
