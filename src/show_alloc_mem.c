#include "libft_malloc.h"

void show_alloc_mem(void)
{
	zone_t* zone;
	block_t* block;

	zone = heap_g;
	while (zone)
	{
		printf("%s : %p\n", (zone->type == 1) ? "TINY" : (zone->type == 2) ? "SMALL" : "LARGE", zone + 1);
		block = (block_t*)(zone + 1);
		while (block)
		{
			printf("%p - %p : %zu bytes\n", block + 1, (char*)(block + 1) + block->size, block->size);
			block = block->next;
		}
		zone = zone->next;
	}
}
