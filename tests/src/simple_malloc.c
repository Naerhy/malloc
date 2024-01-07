#include "libft_malloc.h"

void simple_malloc(void)
{
	void* a;
	void* b;
	void* c;
	void* d;
	void* e;
	void* f;
	void* g;
	void* h;

	write_str("\033[33m===== SIMPLE MALLOC =====\033[00m\n");

	a = malloc(12000);
	b = malloc(5);
	c = malloc(80);
	d = malloc(234);
	e = malloc(201);
	f = malloc(1300);
	g = malloc(1700);
	h = malloc(9223372036854772807);

	write_str("\n");
	show_alloc_mem();
	write_str("\n");

	free(a);
	free(b);
	free(c);
	free(d);
	free(e);
	free(f);
	free(g);
	free(h);

	write_str("\n");
	show_alloc_mem();
	write_str("\n");

	write_str("\033[33m===== SIMPLE MALLOC =====\033[00m\n");
}
