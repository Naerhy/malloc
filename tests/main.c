#include <stdio.h>
#include "libft_malloc.h"

int main(void)
{
	char* str;
	char* temp_1;
	char* temp_2;
	char* temp_3;
	char* temp_4;
	char* temp_5;

	char* temp_6;

	str = temp_malloc(10 * sizeof(char));
	for (int i = 0; i < 9; i++)
		str[i] = 'a' + i;
	str[9] = '\0';

	temp_1 = temp_malloc(1 * sizeof(char));
	temp_2 = temp_malloc(30 * sizeof(char));
	temp_3 = temp_malloc(1 * sizeof(char));
	temp_4 = temp_malloc(12000 * sizeof(char));
	temp_5 = temp_malloc(234 * sizeof(char));

	show_alloc_mem();
	printf("%s\n", str);

	temp_free(str);
	printf("AFTER temp_free\n");
	temp_free(temp_1);
	printf("AFTER temp_free\n");
	temp_free(temp_2);
	printf("AFTER temp_free\n");
	temp_free(temp_3);
	printf("AFTER temp_free\n");
	temp_free(temp_4);
	printf("AFTER temp_free\n");
	temp_free(temp_5);
	printf("AFTER temp_free\n");

	temp_6 = temp_malloc(24 * sizeof(char));

	show_alloc_mem();

	temp_free(temp_6);
	printf("AFTER temp_free\n");

	show_alloc_mem();
	return 0;
}
