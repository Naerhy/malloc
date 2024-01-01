#include "libft_malloc.h"

size_t get_next_mult(size_t x, size_t mult)
{
	return (x - 1) / mult * mult + mult;
}

zone_t* init_zone(int type, size_t size)
{
	zone_t* zone;

	zone = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (zone == MAP_FAILED)
		return NULL;
	zone->type = type;
	zone->size = size - METADATA_ZONE_SIZE;
	zone->free_size = zone->size;
	zone->previous = get_last_zone(heap_g);
	zone->next = NULL;
	return zone;
}

void init_block(zone_t* zone, block_t* block, size_t size, block_t* previous)
{
	block->size = size;
	block->is_free = 0;
	block->previous = previous;
	block->next = NULL;
	if (previous)
		previous->next = block;
	zone->free_size -= size + METADATA_BLOCK_SIZE;
}

block_t* first_fit(size_t size, int type)
{
	zone_t* zone;
	block_t* block;
	block_t* last_block;

	zone = heap_g;
	while (zone)
	{
		if (zone->type == type && zone->free_size >= size + METADATA_BLOCK_SIZE)
		{
			block = (block_t*)(zone + 1);
			while (block)
			{
				if (block->is_free && block->size >= size)
				{
					block->is_free = 0;
					zone->free_size -= size + METADATA_BLOCK_SIZE;
					return block;
				}
				block = block->next;
			}
			if (get_remaining_space(zone) >= size + METADATA_BLOCK_SIZE)
			{
				last_block = get_last_block((block_t*)(zone + 1));
				init_block(zone, (block_t*)((char*)(last_block + 1) + last_block->size),
						size, last_block);
				return (block_t*)((char*)(last_block + 1) + last_block->size);
			}
		}
		zone = zone->next;
	}
	return NULL;
}

size_t get_remaining_space(zone_t const* zone)
{
	block_t* last_block;
	char* start;
	char* end;

	last_block = get_last_block((block_t*)(zone + 1));
	start = (char*)(last_block + 1) + last_block->size;
	end = (char*)(zone + 1) + zone->size;
	return end - start;
}

zone_t* get_last_zone(zone_t* zone)
{
	if (!zone)
		return NULL;
	while (zone->next)
		zone = zone->next;
	return zone;
}

block_t* get_first_block(block_t* block)
{
	if (!block)
		return NULL;
	while (block->previous)
		block = block->previous;
	return block;
}

block_t* get_last_block(block_t* block)
{
	if (!block)
		return NULL;
	while (block->next)
		block = block->next;
	return block;
}

size_t get_total_size(zone_t* zone)
{
	block_t* block;
	size_t total;

	total = 0;
	while (zone)
	{
		block = (block_t*)(zone + 1);
		while (block)
		{
			total += block->size;
			block = block->next;
		}
		zone = zone->next;
	}
	return total;
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

static size_t cst_strlen(char const* str)
{
	size_t length;

	length = 0;
	while (*(str + length))
		length++;
	return length;
}

static void write_char(int c)
{
	write(STDOUT_FILENO, &c, 1);
}

void write_str(char const* str)
{
	write(STDOUT_FILENO, str, cst_strlen(str));
}

static int get_nb_digits(unsigned long nb, unsigned int base)
{
	int nb_digits;

	nb_digits = 1;
	while (nb > base - 1)
	{
		nb /= base;
		nb_digits++;
	}
	return nb_digits;
}

void write_nb(size_t nb)
{
	if (nb > 9)
		write_nb(nb / 10);
	write_char('0' + nb % 10);
}

void write_hex(unsigned long nb, int is_address)
{
	int nb_digits;
	int digit;

	if (is_address)
		write_str("0x");
	nb_digits = get_nb_digits(nb, 16);
	if (!is_address && nb_digits == 1)
		write_char('0');
	for (int i = nb_digits - 1; i >= 0; i--)
	{
		digit = (nb >> (i * 4)) & 0xF;
		write_char(digit < 10 ? '0' + digit : 'a' + (digit - 10));
	}
}
