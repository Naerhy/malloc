#include <stdio.h>
#include "libft_malloc.h"

int main(void)
{
	char* zone;

	zone = temp_malloc(4 * sizeof(char));
	if (!zone)
	{
		printf("malloc is NULL\n");
		return 1;
	}
	for (int i = 0; i < 50; i++)
		printf("%d\n", *(zone + i));
	return 0;
}
