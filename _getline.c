#include "main.h"

/**
 * _getline - used to get characters from the stdout.
 * @lineptr: used to store a single line gotten from
 * the stdout.
 * @semi_seen: used to check if a semi-colon was read
 * from the stdout.
 *
 * Return: ssize_t.
 */
ssize_t _getline(char **lineptr, int **semi_seen)
{
	ssize_t len = 0, x;
	char buffer[999999], c;

	while (read(STDIN_FILENO, &c, 1) > 0)
	{
		buffer[len] = c;
		++len;
		if ((c == '\n') || (c == ';') || (c == '\0'))
		{
			if (c == ';')
				**semi_seen = 1;
			buffer[(len - 1)] = '\0';
			break;
		}
	}
	lineptr[0] = malloc(sizeof(char) * (len + 1));
	if (*lineptr == NULL)
		return (-1);
	x = 0;
	while (x < len)
	{
		lineptr[0][x] = buffer[x];
		++x;
	}
	lineptr[0][x] = '\0';
	return (len);
}

