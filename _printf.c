#include "main.h"

void print_buffered(char buffer[], int *buf_ind);

/**
 * _printf - the main print function
 * @format: character string
 * Return: characters to print
 */
int _printf(const char *format, ...)
{
	int flags, width, precision, size, buf_ind = 0;
	int i, printed = 0, print_chars = 0;
	va_list my_list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(my_list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buf_ind == BUFF_SIZE)
				print_buffer(buffer, &buf_ind);
			print_chars++;
		}
		else
		{
			print_buffer(buffer, &buf_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, my_list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			print_chars += printed;
		}
	}

	print_buffer(buffer, &buf_ind);

	va_end(my_list);

	return (print_chars);
}

/**
 * print_buffer - prints the characters in the buffer
 * @buffer: characters to input in Array
 * @buf_index: the point at wchic to add the character
 */
void print_buffer(char buffer[], int *buf_index)
{
	if (*buf_index > 0)
		write(1, &buffer[0], *buf_index);

	*buf_index = 0;
}
