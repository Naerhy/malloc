#include "libft_malloc.h"

void complex_malloc(void)
{
	void* ptr[5];
	int val1[5] = {4, 14, 122, 20, 12};

	write_str("\033[34m===== COMPLEX MALLOC =====\033[00m\n");

	for (size_t i = 0; i < 5; i++)
		ptr[i] = malloc(val1[i]);

	write_str("\n");
	show_alloc_mem();
	write_str("\n");

	/*
	write_str("\n");
	show_alloc_mem_ex();
	write_str("\n");
	*/

	free(ptr[0]);
	free(ptr[1]);
	free(ptr[3]);
	free(ptr[4]);

	write_str("\n");
	show_alloc_mem();
	write_str("\n");

	/*
	write_str("\n");
	show_alloc_mem_ex();
	write_str("\n");
	*/

	ptr[0] = malloc(16);
	ptr[1] = malloc(30);

	write_str("\n");
	show_alloc_mem();
	write_str("\n");

	ptr[0] = realloc(ptr[0], 0);
	ptr[1] = realloc(ptr[1], 0);
	ptr[2] = realloc(ptr[2], 0);

	write_str("\n");
	show_alloc_mem();
	write_str("\n");

	ptr[0] = realloc(NULL, 130);
	ptr[1] = realloc(NULL, 140);
	ptr[2] = realloc(NULL, 150);

	write_str("\n");
	show_alloc_mem();
	write_str("\n");

	ptr[0] = realloc(ptr[0], 0);
	ptr[1] = realloc(ptr[1], 0);

	write_str("\n");
	show_alloc_mem();
	write_str("\n");

	ptr[0] = malloc(300);

	write_str("\n");
	show_alloc_mem();
	write_str("\n");

	free(ptr[0]);
	free(ptr[2]);

	write_str("\n");
	show_alloc_mem();
	write_str("\n");

	write_str("\033[34m===== COMPLEX MALLOC =====\033[00m\n");
}
