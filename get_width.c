#include "main.h"
/**
 * get_width - Calculate width
 * @format: Formatted string
 * @ptr: List of arguments
 * @args: arguments
 *
 * Return: width
 */
int get_width(const char *format, int *ptr, va_list args)
{
	int curr;
	int width = 0;

	/* Loop through format */
	for (curr = *ptr + 1; format[curr] != '\0'; curr++)
	{

		/* Check for digits and store width */
		if (is_digit(format[curr]))
		{
			width *= 10;
			width += format[curr] - '0';
		}
		else if (format[curr] == '*')
		{
			curr++;
			width = va_arg(args, int);
			break;
		}
		else
			break;
	}

	*ptr = curr - 1;

	return (width);
}
