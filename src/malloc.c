#include "libft_malloc.h"

// TODO remove include
#include <stdio.h>

void* heap_g = NULL;

void* temp_malloc(size_t size)
{
	void* new_zone;
	//void* last_zone;
	rlimit_t limits;

	size = align_size(size);
	if (getrlimit(RLIMIT_AS, &limits) == -1
			|| get_heap_size() + MD_ZONE_SIZE + MD_BLOCK_SIZE + size > limits.rlim_cur)
		return NULL;
	if (size > SMALL_BLOCK_MAX_SIZE)
	{
		new_zone = mmap(NULL, size + MD_ZONE_SIZE + MD_BLOCK_SIZE, PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
		if (!new_zone)
			return NULL;
		((zone_t*)new_zone)->type = 3;
		((zone_t*)new_zone)->size = size + MD_BLOCK_SIZE;
		((zone_t*)new_zone)->free_size = ((zone_t*)new_zone)->size;
		((zone_t*)new_zone)->previous = NULL;
		((zone_t*)new_zone)->next = NULL;
		((block_t*)((zone_t*)new_zone + 1))->size = size;
		((block_t*)((zone_t*)new_zone + 1))->is_free = 0;
		((block_t*)((zone_t*)new_zone + 1))->previous = NULL;
		((block_t*)((zone_t*)new_zone + 1))->next = NULL;
		/*last_zone = get_last_zone();
		if (!last_zone)
			heap_g = new_zone;
		else
			((zone_t*)last_zone)->next = new_zone;
		return (char*)new_zone + MD_ZONE_SIZE + MD_BLOCK_SIZE;*/
		heap_g = new_zone;
		return new_zone;
	}
	return NULL;
}
