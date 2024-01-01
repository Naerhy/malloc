#include "libft_malloc.h"

void show_alloc_mem_ex(void)
{
	zone_t* zone;
	block_t* block;
	unsigned char* start;
	unsigned char* end;

	zone = heap_g;
	while (zone)
	{
		block = (block_t*)(zone + 1);
		while (block)
		{
			start = (unsigned char*)(block + 1);
			end = start + block->size;
			for (int i = 0; start + i < end; i += 8)
			{
				write_hex((unsigned long)(start + i), 1);
				write_str("  ");
				for (int j = 0; j < 8; j++)
				{
					write_hex(*(start + i + j), 0);
					if (j != 7)
						write_str(" ");
					else
						write_str("\n");
				}
			}
			block = block->next;
		}
		zone = zone->next;
	}
}
