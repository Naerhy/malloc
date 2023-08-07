#include <stdio.h>
#include "libft_malloc.h"

int main(void)
{
	char* zone;

	zone = temp_malloc(1000 * sizeof(char));
	if (!zone)
	{
		printf("malloc is NULL\n");
		return 1;
	}
	show_alloc_mem();
	return 0;
}
