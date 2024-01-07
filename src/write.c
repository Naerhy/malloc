#include "libft_malloc.h"

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

static void write_char(int c)
{
	write(STDOUT_FILENO, &c, 1);
}

void write_str(char const* str)
{
	write(STDOUT_FILENO, str, cst_strlen(str));
}

void write_nb(char const* before, size_t nb, char const* after)
{
	if (before)
		write_str(before);
	if (nb > 9)
		write_nb(NULL, nb / 10, NULL);
	write_char('0' + nb % 10);
	if (after)
		write_str(after);
}

void write_hex(char const* before, unsigned long nb, int is_address, char const* after)
{
	int nb_digits;
	int digit;

	if (before)
		write_str(before);
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
	if (after)
		write_str(after);
}
