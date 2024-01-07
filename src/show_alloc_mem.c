#include "libft_malloc.h"

void show_alloc_mem(void)
{
	zone_t* zone;
	block_t* block;

	pthread_mutex_lock(&mutex_g);
	zone = heap_g;
	while (zone)
	{
		write_str((zone->type == 1) ? "TINY : " : (zone->type == 2) ? "SMALL : " : "LARGE : ");
		block = (block_t*)(zone + 1);
		write_hex(NULL, (unsigned long)block, 1, "\n");
		while (block)
		{
			write_hex(NULL, (unsigned long)(block + 1), 1, " - ");
			write_hex(NULL, (unsigned long)((unsigned char*)block + block->size), 1, " : ");
			write_nb(NULL, block->size - METADATA_BLOCK_SIZE, " bytes\n");
			block = block->next;
		}
		zone = zone->next;
	}
	write_nb("Total : ", get_total_size(heap_g), " bytes\n");
	pthread_mutex_unlock(&mutex_g);
}
