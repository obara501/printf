#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include "main.h"
#include <stdio.h>
/**
 * _printf - Custom printf function
 * @format: Format string
 *
 * Return: Number of characters printed (excluding null byte)
 */
int _printf(const char *format, ...)
{
	va_list args;
	int count = 0;
	const char *ptr;

	va_start(args, format);

	for (ptr = format; *ptr != '\0'; ptr++)
	{
		if (*ptr == '%')
		{
			ptr++;
			switch (*ptr)
			{
				case 'c':
					count += _putchar(va_arg(args, int));
					break;
				case 's':
					{
						char *str = va_arg(args, char *);

						count += write(1, str, strlen(str));
					}
					break;
				case '%':
					count += write(1, "%", 1);
					break;
				default:
					count += write(1, "%", 1);
					count += write(1, &(*ptr), 1);
					break;
			}
		}
		else
		{
			count += _putchar(*ptr);
		}
	}

	va_end(args);

	return (count);
}
