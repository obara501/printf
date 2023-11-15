#include "main.h"
/**
 * get_precision - Calculates precision
 * @format: Formatted string
 * @ptr: List of arguments
 * @args: arguments.
 *
 * Return: Precision.
 */
int get_precision(const char *format, int *ptr, va_list args)
{
	int curr = *ptr + 1;
	int precision = -1;

	if (format[curr] != '.')
		return (precision);

	precision = 0;

	/* Loop through formated strting */
	for (curr += 1; format[curr] != '\0'; curr++)
	{
		/* Check for digits and store precison*/
		if (is_digit(format[curr]))
		{
			precision *= 10;
			precision += format[curr] - '0';
		}
		else if (format[curr] == '*')
		{
			curr++;
			precision = va_arg(args, int);
			break;
		}
		else
			break;
	}

	*ptr = curr - 1;

	return (precision);
}
