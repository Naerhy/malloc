#include "libft_malloc.h"

// TODO remove include and use own printf
#include <stdio.h>

void show_alloc_mem(void)
{
	void* temp;
	void* temp2;
	void* first_byte;
	void* last_byte;

	temp = heap_g;
	while (temp)
	{
		if (((zone_t*)temp)->type == 1)
			printf("TINY: %p\n", (char*)temp + MD_ZONE_SIZE);
		else if (((zone_t*)temp)->type == 1)
			printf("SMALL: %p\n", (char*)temp + MD_ZONE_SIZE);
		else
			printf("LARGE: %p\n", (char*)temp + MD_ZONE_SIZE);
		temp2 = (char*)temp + MD_ZONE_SIZE;
		while (temp2)
		{
			first_byte = (char*)temp2 + MD_BLOCK_SIZE;
			last_byte = (char*)temp2 + MD_BLOCK_SIZE + ((block_t*)temp2)->size;
			printf("%p - %p: %lu bytes\n", first_byte, last_byte, last_byte - first_byte);
			temp2 = ((block_t*)temp2)->next;
		}
		temp = ((zone_t*)temp)->next;
		printf("Total: %lu\n", get_total_size());
	}
}
