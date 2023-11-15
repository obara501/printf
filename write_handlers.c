#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * @c: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buffer[],
		int flags, int width, int precision, int size)
{
	int i = 0;
	char padding = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padding = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padding;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @index: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int index, char buffer[],
		int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1;
	char padding = ' ', extra = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';

	if (is_negative)
		extra = '-';

	else if (flags & F_PLUS)
		extra = '+';

	else if (flags & F_SPACE)
		extra = ' ';

	return (write_num(index, buffer, flags, width, precision,
				length, padding, extra));
}

/**
 * write_num - Write a number using a bufffer
 * @index: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision specifier
 * @length: Number length
 * @padding: Pading char
 * @ext: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int index, char buffer[],
		int flags, int width, int prec,
		int length, char padding, char ext)
{
	int i, padding_start = 1;

	if (prec == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0' && width == 0)
		return (0);

	if (prec == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		buffer[index] = padding = ' ';

	if (prec > 0 && prec < length)
		padding = ' ';

	while (prec > length)
		buffer[--index] = '0', length++;

	if (ext != 0)
		length++;

	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padding;

		buffer[i] = '\0';

		if (flags & F_MINUS && padding == ' ')
		{
			if (ext)
				buffer[--index] = ext;

			return (write(1, &buffer[index], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padding == ' ')
		{
			if (ext)
				buffer[--index] = ext;

			return (write(1, &buffer[1], i - 1) + write(1, &buffer[index], length));
		}
		else if (!(flags & F_MINUS) && padding == '0')
		{
			if (ext)
				buffer[--padding_start] = ext;

			return (write(1, &buffer[padding_start], i - padding_start) +
					write(1, &buffer[index], length - (1 - padding_start)));
		}
	}
	if (ext)
		buffer[--index] = ext;

	return (write(1, &buffer[index], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indexicating if the num is negative
 * @index: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifie
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int index,
		char buffer[],
		int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1, i = 0;
	char padding = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		return (0);

	if (precision > 0 && precision < length)
		padding = ' ';

	while (precision > length)
	{
		buffer[--index] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padding;

		buffer[i] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[index], length) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[index], length));
		}
	}
	return (write(1, &buffer[index], length));
}

/**
 * write_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @index: Starting index
 * @length: Length
 * @width: Wwidth
 * @flags: Flags
 * @padding: Padding
 * @ext:Extra character
 * @padding_start: Index at which padding starts
 *
 * Return: Count characters
 */
int write_pointer(char buffer[], int index, int length,
		int width, int flags, char padding, char ext, int padding_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padding;

		buffer[i] = '\0';

		if (flags & F_MINUS && padding == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';

			if (ext)
				buffer[--index] = ext;

			return (write(1, &buffer[index], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padding == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';

			if (ext)
				buffer[--index] = ext;

			return (write(1, &buffer[3], i - 3) + write(1, &buffer[index], length));
		}
		else if (!(flags & F_MINUS) && padding == '0')
		{
			if (ext)
				buffer[--padding_start] = ext;

			buffer[1] = '0';
			buffer[2] = 'x';

			return (write(1, &buffer[padding_start], i - padding_start) +
					write(1, &buffer[index], length - (1 - padding_start) - 2));
		}
	}
	buffer[--index] = 'x';
	buffer[--index] = '0';

	if (ext)
		buffer[--index] = ext;

	return (write(1, &buffer[index], BUFF_SIZE - index - 1));
}
