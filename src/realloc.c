#include "libft_malloc.h"

void* realloc(void* ptr, size_t size)
{
	void* new_alloc;
	size_t old_size;

	if (!ptr)
		return malloc(size);
	if (!size)
	{
		free(ptr);
		return NULL;
	}
	old_size = ((block_t*)ptr - 1)->size - METADATA_BLOCK_SIZE;
	if (size == old_size)
		return ptr;
	new_alloc = malloc(size);
	if (!new_alloc)
		return NULL;
	cst_memcpy(new_alloc, ptr, size < old_size ? size : old_size);
	free(ptr);
	return new_alloc;
}
