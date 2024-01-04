#include "libft_malloc.h"

void simple_malloc(void);
void lots_of_mallocs(void);
void complex_malloc(void);
void multithreaded_malloc(void);

int main(void)
{
	simple_malloc();
	lots_of_mallocs();
	complex_malloc();
	multithreaded_malloc();
	return 0;
}
