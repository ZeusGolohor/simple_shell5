#include "main.h"

ssize_t _getline_check(char *lineptr)
{
	ssize_t i = 0, seen = 0;

	while (lineptr[i] != '\0')
	{
		if ((lineptr[i] >= 'a' && lineptr[i] >= 'z') || (lineptr[i] >= 'A' && lineptr[i] <= 'Z'))
		seen  = 1;
		++i;
	}
	return (seen);
}
