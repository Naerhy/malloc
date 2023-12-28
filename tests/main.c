#include <stdio.h>
#include "libft_malloc.h"

int main(void)
{
	char* zone;

	zone = temp_malloc(1 * sizeof(char));
	printf("1\n");
	zone = temp_malloc(1 * sizeof(char));
	printf("2\n");
	zone = temp_malloc(12000 * sizeof(char));
	printf("3\n");
	zone = temp_malloc(1 * sizeof(char));
	zone = temp_malloc(200 * sizeof(char));
	zone = temp_malloc(240 * sizeof(char));
	if (!zone)
	{
		printf("malloc is NULL\n");
		return 1;
	}
	char* str = temp_malloc(10 * sizeof(char));
	if (!str)
		return 1;
	for (int i = 0; i < 9; i++)
		str[i] = 'a' + i;
	str[9] = '\0';
	printf("%s\n", str);
	show_alloc_mem();
	return 0;
}
