#include "main.h"
/****************** PRINT POINTER VARIABLE ******************/
/**
* print_pointer - Print the value of a pointer variable
* @args: List a of arguments
* @buffer: Buffer array to handle print
* @flags: Calculates active flags
* @width: get width
* @precision: Precision specification
* @size: Size specifier
* Return: Number of chars printed.
*/
int print_pointer(va_list args, char buffer[],
int flags, int width, int precision, int size)
{
char extra_char = 0, padd = ' ';
int index = BUFF_SIZE - 2, length = 2, padd_start = 1;
unsigned long num_adrs;
char map_to[] = "0123456789abcdef";
void *adrs = va_arg(args, void *);
UNUSED(width);
UNUSED(size);
if (adrs == NULL)
return (write(1, "(nil)", 5));
buffer[BUFF_SIZE - 1] = '\0';
UNUSED(precision);
num_adrs = (unsigned long)adrs;
while (num_adrs > 0)
{
buffer[index--] = map_to[num_adrs % 16];
num_adrs /= 16;
length++;
}
if ((flags & F_ZERO) && !(flags & F_MINUS))
padd = '0';
if (flags & F_PLUS)
extra_char = '+', length++;
else if (flags & F_SPACE)
extra_char = ' ', length++;
index++;
return (write_pointer(buffer, index, length,
width, flags, padd, extra_char, padd_start));
}
/************************* PRINT NON PRINTABLE *************************/
/**
* print_non_printable - Print ASCII codes in hexa of non printable chars
* @args: List a of arguments
* @buffer: Buffer array to handle print
* @flags: Calculates active flags
* @width: get width
* @precision: Precision specification
* @size: Size specifier
* Return: Number of chars printed
*/
int print_non_printable(va_list args, char buffer[],
int flags, int width, int precision, int size)
{
int x = 0, offset = 0;
char *string = va_arg(args, char *);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);
if (string == NULL)
return (write(1, "(null)", 6));
while (string[x] != '\0')
{
if (is_printable(string[x]))
buffer[x + offset] = string[x];
else
offset += append_hexa_code(string[x], buffer, x + offset);
x++;
}
buffer[x + offset] = '\0';
return (write(1, buffer, x + offset));
}
/************************* PRINT IN REVERSE *************************/
/**
* print_reverse - Print string in reverse.
* @args: List a of arguments
* @buffer: Buffer array to handle print
* @flags: Calculates active flags
* @width: get width
* @precision: Precision specification
* @size: Size specifier
* Return: Numbers of chars printed
*/
int print_reverse(va_list args, char buffer[],
int flags, int width, int precision, int size)
{
char *string;
int a, counter = 0;
UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(size);
string = va_arg(args, char *);
if (string == NULL)
{
UNUSED(precision);
string = ")Null(";
}
for (a = 0; string[a]; a++)
;
for (a = a - 1; a >= 0; a--)
{
char z = string[a];
write(1, &z, 1);
counter++;
}
return (counter);
}
/************************* PRINT STRING IN ROT13 *************************/
/**
* print_rot13string - Print string in rot13.
* @args: List a of arguments
* @buffer: Buffer array to handle print
* @flags: Calculates active flags
* @width: get width
* @precision: Precision specification
* @size: Size specifier
* Return: Numbers of chars printed
*/
int print_rot13string(va_list args, char buffer[],
int flags, int width, int precision, int size)
{
char a;
char *string;
unsigned int x, y;
int counter = 0;
char in[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
char out[] =
"NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";
string = va_arg(args, char *);
UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);
if (string == NULL)
string = "(AHYY)";
for (x = 0; string[x]; x++)
{
for (y = 0; in[y]; y++)
{
if (in[y] == string[x])
{
x = out[y];
write(1, &a, 1);
counter++;
break;
}
}
if (!in[y])
{
x = string[x];
write(1, &a, 1);
counter++;
}
}
return (counter);
}
