#include "libft_malloc.h"

int cst_atoi(char const* str)
{
	int result;

	result = 0;
	while (*str)
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return result;
}

void* cst_memcpy(void* dest, void const* src, size_t n)
{
	unsigned char* udest;
	unsigned char const* usrc;

	udest = dest;
	usrc = src;
	for (size_t i = 0; i < n; i++)
		*(udest + i) = *(usrc + i);
	return dest;
}

size_t cst_strlen(char const* str)
{
	size_t length;

	length = 0;
	while (*(str + length))
		length++;
	return length;
}
