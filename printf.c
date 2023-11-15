#include "main.h"

void print_buffer(char buffer[], int *buff);

/**
 * _printf - The custopm _printf function.
 * @format: Format string
 *
 * Return: Number of characters printed (excluding null byte)
 */
int _printf(const char *format, ...)
{
	va_list args;
	char buffer[BUFF_SIZE];

	int ptr, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_index = 0;

	if (format == NULL)
		return (-1);

	/* Call va_start macro */
	va_start(args, format);

	/* Loop through format string for modifier */
	for (ptr = 0; format && format[ptr] != '\0'; ptr++)
	{
		if (format[ptr] != '%')
		{
			buffer[buff_index++] = format[ptr];
			if (buff_index == BUFF_SIZE)
				print_buffer(buffer, &buff_index);
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_index);
			flags = get_flags(format, &ptr);
			width = get_width(format, &ptr, args);
			precision = get_precision(format, &ptr, args);
			size = get_size(format, &ptr);
			++ptr;

			printed = do_print(format, &ptr, args, buffer,
					flags, width, precision, size);

			if (printed == -1)
				return (-1);

			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_index);

	va_end(args);

	return (printed_chars);
}

/**
 * print_buffer - Prints the content of the buffer
 * @buffer: Array of characters
 * @buff_index: Index at which to add next char, also length
 */
void print_buffer(char buffer[], int *buff_index)
{
	if (*buff_index > 0)
		write(1, &buffer[0], *buff_index);

	*buff_index = 0;
}
