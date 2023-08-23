#include "main.h"
/**
 * print_characters -prints the desired character
 * @my_types: the list of arguments inputed
 * @buffer: array of buffer to print
 * @flags: an int value of active flags
 * @width: the width
 * @precision: the precision
 * @size: size of characters
 * Return: number of characters to print
 */
int print_character(va_list my_types, char buffer[],
		int flags, int width, int precision, int size)
{
	char c = va_args(my_types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/**
 * print_strings - prints a set of strings
 * @my_types: list of arguments supplied
 * @buffer: array of buffer to print
 * @flags: an int value of active flags
 * @width: the width
 * @precision: the precision
 * @size: the size of characters
 * Return: the strings to print
 */

int print_strings(va_list my_types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(my_types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}

/***
 * print_percent - prints percentage
 * @my_types: the list of arguments
 * @buffer: the character buffer
 * @flags: the flags
 * @width: width
 * @precision: the precision specifier
 * @size: the size of character
 */

int print_percent(va_list my_types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(my_types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}
/**
 * print_integer - print an integer
 * @my_types: list of arguments
 * @buffer: the buffer character
 * @flags: the flags accepted
 * @width: the width
 * @precision: the precision
 * @size: size of the characters
 */

int print_integer(va_list my_types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(my_types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}
