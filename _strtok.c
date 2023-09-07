#include "main.h"

char **_strtok(char *lineptr, ssize_t **arr_size)
{
	ssize_t i = 0, x = 0, y = 0, z = 0;
	char **args;
	char cmds[100];

	if ((lineptr[0] == '\0') || (lineptr[0] == '#'))
		return (NULL);
	while ((lineptr[i] == ' ') && (lineptr[i] != '\0'))
		++i;
	if (lineptr[i] == '\0')
		return (NULL);	
	while ((lineptr[i] != '\0') && (lineptr[i] != '#' || lineptr[(i - 1)] != ' '))
	{
		if ((lineptr[(i + 1)] != '\0') && (lineptr[(i + 1)] != '#' || lineptr[i] != ' '))
		{
			if ((lineptr[i] == ' ') && (lineptr[(i + 1)] != ' ' || lineptr[i] != ' '))
				**arr_size = **arr_size + 1;
		}
		++i;
	}
	args = malloc(sizeof(char *) * (**arr_size + 1));
	if (args == NULL)
		return (NULL);
	x = 0;
	while(x < **arr_size)
	{
		while ((lineptr[y] == ' ') && (lineptr[y] != '\0') && (lineptr[y] != '#' || lineptr[(i - 1)] != ' '))
			++y;
		z = 0;
		while ((lineptr[y] != ' ') && (lineptr[y] != '\0') && (lineptr[y] != '\n') && (lineptr[y] != '#' || lineptr[(i - 1)] != ' '))
		{
			if (lineptr[y] != ' ')
			{
				cmds[z] = lineptr[y];
				++z;
			}
			++y;
		}
		cmds[z] = '\0';
		if ((x == 0) && (cmds[0] != '/'))
		{
			args[x] = malloc(sizeof(char) * (strlen(cmds) + 1 + 5));
			if (args[x] == NULL)
				return (NULL);
			args[x][0] = '\0';
			strcat(args[x], "/bin/");
			strcat(args[x], cmds);
			if (access(args[x], F_OK) != 0)
			{
				free(args[x]);
				args[x] = malloc(sizeof(char) * (strlen(cmds) + 1));
				if (args[x] == NULL)
					return (NULL);
				args[x][0] = '\0';
				strcat(args[x], cmds);
			}
		}
		else
		{
			args[x] = malloc(sizeof(char) * (strlen(cmds) + 1));
			if (args[x] == NULL)
				return (NULL);
			args[x][0] = '\0';
			strcat(args[x], cmds);
			if (args[x][0] == 0)
				args[x] = NULL;
		}
		++x;
	}
	args[**arr_size] = NULL;
	**arr_size = 1;
	cmds[0] = '\0';
	return (args);
}

