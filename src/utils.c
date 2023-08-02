#include "libft_malloc.h"

size_t align_size(size_t size)
{
	return (((size - 1) >> 2) << 2) + 4;
}
