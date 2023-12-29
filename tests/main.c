#include <stdio.h>
#include "libft_malloc.h"

int main(void)
{
	void* a;
	void* b;
	void* c;
	void* d;
	void* e;

	a = temp_malloc(10 * sizeof(char));
	b = temp_malloc(20000 * sizeof(char));
	c = temp_malloc(300 * sizeof(char));
	d = temp_malloc(2 * sizeof(char));
	e = temp_malloc(150 * sizeof(char));

	printf("=====================\n");
	show_alloc_mem();
	printf("=====================\n");

	temp_free(a);
	temp_free(b);
	temp_free(c);
	temp_free(d);
	temp_free(e);

	printf("=====================\n");
	show_alloc_mem();
	printf("=====================\n");

	a = temp_malloc(3000 * sizeof(char));
	b = temp_malloc(345 * sizeof(char));
	c = temp_malloc(2000 * sizeof(char));
	d = temp_malloc(1 * sizeof(char));
	e = temp_malloc(1 * sizeof(char));

	printf("=====================\n");
	show_alloc_mem();
	printf("=====================\n");

	temp_free(b);
	temp_free(c);
	temp_free(d);

	printf("=====================\n");
	show_alloc_mem();
	printf("=====================\n");

	b = temp_malloc(8 * sizeof(char));

	printf("=====================\n");
	show_alloc_mem();
	printf("=====================\n");

	return 0;
}
