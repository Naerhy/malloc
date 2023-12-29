#include "libft_malloc.h"

void* temp_realloc(void* ptr, size_t size)
{
	void* new_alloc;
	size_t old_size;

	if (!ptr)
		return temp_malloc(size);
	if (!size)
	{
		temp_free(ptr);
		return NULL;
	}
	new_alloc = temp_malloc(size);
	if (!new_alloc)
		return NULL;
	old_size = ((block_t*)ptr - 1)->size;
	cst_memcpy(new_alloc, ptr, (size < old_size) ? size : old_size);
	temp_free(ptr);
	return new_alloc;
}
