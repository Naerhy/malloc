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

static int valid_number(char const* str)
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

static size_t count_zones(zone_t* zone)
{
	size_t count;

	count = 0;
	while (zone)
	{
		count++;
		zone = zone->next;
	}
	return count;
}

int check_max_zones(void)
{
	char* env;
	size_t max_zones;
	size_t nb_zones;

	env = getenv("FT_MALLOC_MAX_ZONES");
	if (env && valid_number(env))
	{
		max_zones = cst_atoi(env);
		nb_zones = count_zones(heap_g);
		if (max_zones == nb_zones)
			return 0;
	}
	return 1;
}

int check_max_size(size_t size)
{
	char* env;
	size_t max_size;

	env = getenv("FT_MALLOC_MAX_SIZE");
	if (env && valid_number(env))
	{
		max_size = cst_atoi(env);
		if (size > max_size)
			return 0;
	}
	return 1;
}
