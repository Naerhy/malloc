#include <stdio.h>
#include "libft_malloc.h"

int main(void)
{
	char* zone;

	zone = malloc(100000 * sizeof(char));
	for (int i = 0; i < 50; i++)
		printf("%d\n", *(zone + i));
	return 0;
}
