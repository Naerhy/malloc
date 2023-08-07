#include "libft_malloc.h"

size_t align_size(size_t size)
{
	return (((size - 1) >> 2) << 2) + 4;
}

size_t get_heap_size(void)
{
	size_t size;

	size = 0;
	while (heap_g)
	{
		size += ((zone_t*)heap_g)->size;
		heap_g = ((zone_t*)heap_g)->next;
	}
	return size;
}

void* get_last_zone(void)
{
	void* temp;

	temp = heap_g;
	while (((zone_t*)temp)->next)
		temp = ((zone_t*)temp)->next;
	return temp;
}

size_t get_total_size(void)
{
	void* temp;
	void* temp2;
	size_t size;

	size = 0;
	temp = heap_g;
	while (temp)
	{
		temp2 = (char*)temp + MD_ZONE_SIZE;
		while (temp2)
		{
			size += ((block_t*)temp2)->size;
			temp2 = ((block_t*)temp2)->next;
		}
		temp = ((zone_t*)temp)->next;
	}
	return size;
}
