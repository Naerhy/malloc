#include "libft_malloc.h"

int main(void)
{
	void* a;
	void* b;
	void* c;
	void* d;
	void* e;

	write(1, "====================\n", 21);
	show_alloc_mem();
	write(1, "====================\n", 21);

	a = malloc(10 * sizeof(char));
	b = malloc(20000 * sizeof(char));
	c = malloc(300 * sizeof(char));
	d = malloc(2 * sizeof(char));
	e = malloc(150 * sizeof(char));

	write(1, "====================\n", 21);
	show_alloc_mem();
	write(1, "====================\n", 21);

	free(a);
	free(b);
	free(c);
	free(d);
	free(e);

	write(1, "====================\n", 21);
	show_alloc_mem();
	write(1, "====================\n", 21);

	a = malloc(3000 * sizeof(char));
	b = malloc(345 * sizeof(char));
	c = malloc(2000 * sizeof(char));
	d = malloc(1 * sizeof(char));
	e = malloc(1 * sizeof(char));

	write(1, "====================\n", 21);
	show_alloc_mem();
	write(1, "====================\n", 21);

	free(b);
	free(c);
	free(d);

	write(1, "====================\n", 21);
	show_alloc_mem();
	write(1, "====================\n", 21);

	b = malloc(8 * sizeof(char));

	write(1, "====================\n", 21);
	show_alloc_mem();
	write(1, "====================\n", 21);

	// REMOVE VARIABLES ASSIGNEMENT
	a = realloc(a, 0);
	b = realloc(b, 0);
	c = realloc(e, 0);

	write(1, "====================\n", 21);
	show_alloc_mem();
	write(1, "====================\n", 21);

	a = realloc(NULL, 120);
	b = realloc(NULL, 4500);
	c = realloc(NULL, 80);

	write(1, "====================\n", 21);
	show_alloc_mem();
	write(1, "====================\n", 21);

	free(a);
	free(b);
	e = realloc(NULL, 110);

	write(1, "====================\n", 21);
	show_alloc_mem();
	write(1, "====================\n", 21);

	e = realloc(e, 3456);
	e = realloc(e, 0);

	write(1, "====================\n", 21);
	show_alloc_mem();
	write(1, "====================\n", 21);

	return 0;
}
