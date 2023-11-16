#include "main.h"
/************************* PRINT UNSIGNED NUMBER *************************/
/**
* print_unsigned - Function to print an unsigned number
* @args: List a of arguments
* @buffer: Buffer array to handle print
* @flags: Calculates active flags
* @width: get width
* @precision: Precision specification
* @size: Size specifier
* Return: Number of chars printed.
*/
int print_unsigned(va_list args, char buffer[],
int flags, int width, int precision, int size)
{
int a = BUFF_SIZE - 2;
unsigned long int number = va_arg(args, unsigned long int);
number = convert_size_unsgnd(number, size);
if (number == 0)
buffer[a--] = '0';
buffer[BUFF_SIZE - 1] = '\0';
while (number > 0)
{
buffer[a--] = (number % 10) + '0';
number /= 10;
}
a++;
return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}
/************* PRINT UNSIGNED NUMBER IN OCTAL NOTATION ****************/
/**
* print_octal - Function to print an unsigned number in octal notation
* @args: List a of arguments
* @buffer: Buffer array to handle print
* @flags: Calculates active flags
* @width: get width
* @precision: Precision specification
* @size: Size specifier
* Return: Number of chars printed
*/
int print_octal(va_list args, char buffer[],
int flags, int width, int precision, int size)
{
int a = BUFF_SIZE - 2;
unsigned long int number = va_arg(args, unsigned long int);
unsigned long int init_number = number;
UNUSED(width);
number = convert_size_unsgnd(number, size);
if (number == 0)
buffer[a--] = '0';
buffer[BUFF_SIZE - 1] = '\0';
while (number > 0)
{
buffer[a--] = (number % 8) + '0';
number /= 8;
}
if (flags & F_HASH && init_number != 0)
buffer[a--] = '0';
a++;
return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}
/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL NOTATION **************/
/**
* print_hexadecimal - Prints an unsigned number in hexadecimal notation
* @args: List a of arguments
* @buffer: Buffer array to handle print
* @flags: Calculates active flags
* @width: get width
* @precision: Precision specification
* @size: Size specifier
* Return: Number of chars printed
*/
int print_hexadecimal(va_list args, char buffer[],
int flags, int width, int precision, int size)
{
return (print_hexa(args, "0123456789abcdef", buffer,
flags, 'x', width, precision, size));
}
/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
* print_hexa_upper - Print an unsigned number in upper hexadecimal notation
* @args: List a of arguments
* @buffer: Buffer array to handle print
* @flags: Calculates active flags
* @width: get width
* @precision: Precision specification
* @size: Size specifier
* Return: Number of chars printed
*/
int print_hexa_upper(va_list args, char buffer[],
int flags, int width, int precision, int size)
{
return (print_hexa(args, "0123456789ABCDEF", buffer,
flags, 'X', width, precision, size));
}
/************** PRINT HEXADECIMAL NUMBER IN LOWER OR UPPER **************/
/**
* print_hexa - Function to print a hexadecimal number in lower or upper
* @args: List a of arguments
* @map_to: Array of values to map the number to
* @buffer: Buffer array to handle print
* @flags: Calculates active flags
* @flag_ch: Calculates active flags
* @width: get width
* @precision: Precision specification
* @size: Size specifier
* @size: Size specification
* Return: Number of chars printed
*/
int print_hexa(va_list args, char map_to[], char buffer[],
int flags, char flag_ch, int width, int precision, int size)
{
int a = BUFF_SIZE - 2;
unsigned long int number = va_arg(args, unsigned long int);
unsigned long int init_number = number;
UNUSED(width);
number = convert_size_unsgnd(number, size);
if (number == 0)
buffer[a--] = '0';
buffer[BUFF_SIZE - 1] = '\0';
while (number > 0)
{
buffer[a--] = map_to[number % 16];
number /= 16;
}
if (flags & F_HASH && init_number != 0)
{
buffer[a--] = flag_ch;
buffer[a--] = '0';
}
a++;
return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}
