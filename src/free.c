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
		combined_size = first->size + second->size;
		if (enough_size(combined_size - METADATA_BLOCK_SIZE, type))
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
	munmap(zone, zone->size);
}

static size_t get_nb_zones(zone_t* zone, int type)
{
	size_t count;

	count = 0;
	while (zone)
	{
		if (zone->type == type)
			count++;
		zone = zone->next;
	}
	return count;
}

void free(void* ptr)
{
	block_t* block;
	zone_t* zone;

	pthread_mutex_lock(&mutex_g);
	if (ptr && valid_ptr(heap_g, ptr))
	{
		block = (block_t*)ptr - 1;
		block->is_free = 1;
		zone = (zone_t*)(block->previous ? get_first_block(block) : block) - 1;
		zone->free_size += block->size;
		try_merge_blocks(block->previous, block, zone->type);
		try_merge_blocks(block, block->next, zone->type);
		if (zone->free_size == zone->size - METADATA_ZONE_SIZE)
		{
			if (zone->type != 3 && get_nb_zones(heap_g, zone->type) == 1)
				((block_t*)(zone + 1))->next = NULL;
			else
				release_memory(zone);
		}
	}
	pthread_mutex_unlock(&mutex_g);
}
