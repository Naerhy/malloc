#include "libft_malloc.h"

void show_alloc_mem(void)
{
	zone_t* zone;
	block_t* block;

	zone = heap_g;
	while (zone)
	{
		write_str((zone->type == 1) ? "TINY : " : (zone->type == 2) ? "SMALL : " : "LARGE : ");
		write_ptr((unsigned long)(zone + 1));
		write_str("\n");
		block = (block_t*)(zone + 1);
		while (block)
		{
			write_ptr((unsigned long)(block + 1));
			write_str(" - ");
			write_ptr((unsigned long)((char*)(block + 1) + block->size));
			write_str(" : ");
			write_nb(block->size);
			write_str(" bytes\n");
			block = block->next;
		}
		zone = zone->next;
	}
}
