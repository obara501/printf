#include "main.h"

/**
 * is_printable - Checks if a character is printable
 * @c: Character to be evaluated.
 *
 * Return: 1 if c is printable, 0 otherwise
 */
int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * is_digit - Check if a character is a digit
 * @c: Character to be evaluated
 *
 * Return: 1 if c is a digit, 0 otherwise
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Convert a number to a specific size
 * @num: Number to be coverted.
 * @size: Number indicating the type to be converted to..
 *
 * Return: Casted value of number
 */
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}
