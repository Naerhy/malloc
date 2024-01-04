#include <unistd.h>
#include "libft_malloc.h"

static void* thread_func(void* arg)
{
	void* ptr[30];
	int* size;

	size = (int*)arg;
	for (size_t i = 0; i < 30; i++)
	{
		ptr[i] = malloc(*size);
		usleep(10);
	}

	/*
	for (size_t i = 0; i < 30; i++)
		free(ptr[i]);
	*/
	(void)ptr;

	return NULL;
}

void multithreaded_malloc(void)
{
	pthread_t tid[3];
	size_t sizes[3] = {200, 220, 240};

	write_str("\033[32m===== MULTITHREADED MALLOC =====\033[00m\n");

	for (size_t i = 0; i < 3; i++)
		pthread_create(&tid[i], NULL, thread_func, &sizes[i]);

	write_char('\n');
	show_alloc_mem();
	write_char('\n');

	for (size_t i = 0; i < 3; i++)
		pthread_join(tid[i], NULL);

	write_str("\033[32m===== MULTITHREADED MALLOC =====\033[00m\n");
}
