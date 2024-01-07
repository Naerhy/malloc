#include "libft_malloc.h"

void show_alloc_mem_ex(void)
{
	zone_t* zone;
	block_t* block;
	unsigned char* start;
	unsigned char* end;

	pthread_mutex_lock(&mutex_g);
	zone = heap_g;
	while (zone)
	{
		block = (block_t*)(zone + 1);
		while (block)
		{
			start = (unsigned char*)(block + 1);
			end = (unsigned char*)block + block->size;
			for (int i = 0; start + i < end; i += 8)
			{
				write_hex(NULL, (unsigned long)(start + i), 1, "  ");
				for (int j = 0; j < 8; j++)
					write_hex(NULL, *(start + i + j), 0, j != 7 ? " " : "\n");
			}
			block = block->next;
		}
		zone = zone->next;
	}
	pthread_mutex_unlock(&mutex_g);
}
