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

	if (!a || !b || !c || !d || !e)
	{
		write(STDOUT_FILENO, "ERROR\n", 6);
		return 1;
	}

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
	free(c);

	write(1, "====================\n", 21);
	show_alloc_mem();
	write(1, "====================\n", 21);

	a = malloc(15 * sizeof(char));

	write(1, "====================\n", 21);
	show_alloc_mem();
	write(1, "====================\n", 21);
	show_alloc_mem_ex();
	write(1, "====================\n", 21);

	char* tt = a;
	for (int i = 0; i < 4; i++)
		tt[i] = 13 + i * 2;

	write(1, "====================\n", 21);
	show_alloc_mem_ex();
	write(1, "====================\n", 21);

	free(tt);
	a = malloc(sizeof(char) * 8);
	b = malloc(sizeof(char) * 8);
	c = malloc(sizeof(char) * 8);

	write(1, "====================\n", 21);
	show_alloc_mem();
	write(1, "====================\n", 21);

	free(a);
	free(b);

	write(1, "====================\n", 21);
	show_alloc_mem();
	write(1, "====================\n", 21);
	return 0;
}
