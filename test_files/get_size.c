#include "main.h"
/**
 * get_size - Calculates the size
 * @format: Formatted string
 * @ptr: List of arguments
 *
 * Return: Size.
 */
int get_size(const char *format, int *ptr)
{
	int i = *ptr + 1;
	int size = 0;


	if (format[i] == 'l')
		size = S_LONG;

	else if (format[i] == 'h')
		size = S_SHORT;

	if (size == 0)
		*ptr = i - 1;
	else
		*ptr = i;

	return (size);
}
