#include "libft_malloc.h"

// if size > SMALL_BLOCK_MAX_SIZE
//   check memory limit (getrlimit)
//     if > limit return NULL
// else if size > TINY_BLOCK_MAX_SIZE
// else

// TODO remove include
#include <stdio.h>

void* heap_g = NULL;

void* temp_malloc(size_t size)
{
	//void* new_zone;
	struct rlimit limit;

	if (getrlimit(RLIMIT_AS, &limit) == -1)
	{
		printf("getrlimit error\n");
		return NULL;
	}
	printf("%lu - %lu\n", limit.rlim_cur, limit.rlim_max);
	printf("original size = %lu | aligned size = %lu\n", size, align_size(size));
	/*(if (size > SMALL_BLOCK_MAX_SIZE)
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
	}
	return new_zone;*/
	return NULL;
}
