#include "libft_malloc.h"

size_t align_size(size_t x, size_t align)
{
	return (x - 1) / align * align + align;
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
	fill_block(block);
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
				if (block->is_free && size <= block->size)
				{
					block->is_free = 0;
					fill_block(block);
					zone->free_size -= block->size + METADATA_BLOCK_SIZE;
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

int valid_ptr(void* ptr)
{
	zone_t* zone;
	block_t* block;

	zone = heap_g;
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

int valid_number(char const* str)
{
	if (!cst_strlen(str))
		return 0;
	for (size_t i = 0; *(str + i); i++)
	{
		if (*(str + i) < '0' || *(str + i) > '9')
			return 0;
	}
	return 1;
}

int check_max_zones(void)
{
	char* env;
	int max_zones;
	size_t nb_zones;

	env = getenv("FT_MALLOC_MAX_ALLOC");
	if (env && valid_number(env))
	{
		max_zones = cst_atoi(env);
		nb_zones = get_nb_zones(heap_g);
		if ((size_t)max_zones == nb_zones)
			return 0;
	}
	return 1;
}

int check_max_size(size_t size)
{
	char* env;
	int max_size;

	env = getenv("FT_MALLOC_MAX_SIZE");
	if (env && valid_number(env))
	{
		max_size = cst_atoi(env);
		if ((size_t)max_size < size)
			return 0;
	}
	return 1;
}

void fill_block(block_t* block)
{
	char* env;
	char* start;

	env = getenv("FT_MALLOC_VALUE");
	if (env && valid_number(env) && cst_atoi(env))
	{
		start = (char*)(block + 1);
		for (size_t i = 0; i < block->size; i++)
			*(start + i) = 42;
	}
}
