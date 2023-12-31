#include "libft_malloc.h"

void lots_of_mallocs(void)
{
	void* ptr[100];

	write_str("\033[31m===== LOTS OF MALLOCS =====\033[00m\n");

	for (size_t i = 0; i < 100; i++)
		ptr[i] = malloc(sizeof(int) * i + 1);

	write_str("\n");
	show_alloc_mem();
	write_str("\n");

	for (size_t i = 0; i < 100; i++)
		free(ptr[i]);

	write_str("\n");
	show_alloc_mem();
	write_str("\n");

	write_str("\033[31m===== LOTS OF MALLOCS =====\033[00m\n");
}
