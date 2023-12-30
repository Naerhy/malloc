#include <stdio.h>
#include "libft_malloc.h"

int main(void)
{
	void* a;
	void* b;
	void* c;
	void* d;
	void* e;

	a = malloc(10 * sizeof(char));
	b = malloc(20000 * sizeof(char));
	c = malloc(300 * sizeof(char));
	d = malloc(2 * sizeof(char));
	e = malloc(150 * sizeof(char));

	printf("=====================\n");
	show_alloc_mem();
	printf("=====================\n");

	free(a);
	free(b);
	free(c);
	free(d);
	free(e);

	printf("=====================\n");
	show_alloc_mem();
	printf("=====================\n");

	a = malloc(3000 * sizeof(char));
	b = malloc(345 * sizeof(char));
	c = malloc(2000 * sizeof(char));
	d = malloc(1 * sizeof(char));
	e = malloc(1 * sizeof(char));

	printf("=====================\n");
	show_alloc_mem();
	printf("=====================\n");

	free(b);
	free(c);
	free(d);

	printf("=====================\n");
	show_alloc_mem();
	printf("=====================\n");

	b = malloc(8 * sizeof(char));

	printf("=====================\n");
	show_alloc_mem();
	printf("=====================\n");

	// REMOVE VARIABLES ASSIGNEMENT
	a = realloc(a, 0);
	b = realloc(b, 0);
	c = realloc(e, 0);

	printf("=====================\n");
	show_alloc_mem();
	printf("=====================\n");

	a = realloc(NULL, 120);
	b = realloc(NULL, 4500);
	c = realloc(NULL, 80);

	printf("=====================\n");
	show_alloc_mem();
	printf("=====================\n");

	free(a);
	free(b);
	e = realloc(NULL, 110);

	printf("=====================\n");
	show_alloc_mem();
	printf("=====================\n");

	e = realloc(e, 3456);
	e = realloc(e, 0);

	printf("=====================\n");
	show_alloc_mem();
	printf("=====================\n");

	return 0;
}
