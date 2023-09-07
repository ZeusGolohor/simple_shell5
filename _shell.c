#include "main.h"

/**
 * main - program entry point.
 * @ac: number of arguements passed to the program through
 * the terminal.
 * @av: an array of pointers to the arguements passed to the
 * program.
 *
 * Return: int.
 */
int main(int ac, char **av)
{
	int status = 0, *_status = &status, **__status = &_status;
	env_t *_env = NULL, **env = &_env;
	char *_envi = NULL, **envi = &_envi;

	signal(SIGINT, _ctrl_c_handler);
	_setup_env_nodes(env);
	_setup_env(env, &envi);
	_shell(ac, av, envi, __status, env);
	_free_env_nodes(env);
	_free_env(envi);
	return (0);
}

/**
 * _shell - A function used to start a simple shell.
 * @ac: number of arguements passed to the program.
 * @av: an array of pointers to the arguements passed to the program.
 * @env: a pointer to a pointer to the OS environment variables
 * stored in a linked list.
 * @envi: a pointer to a pointer to the OS environment variables.
 * @status: used to hold the status of the previously executed forked command.
 *
 * Return: void.
 */
void _shell(__attribute__((unused)) int ac, char **av,
char **envi, int **status, env_t **env)
{
	ssize_t size = -1, arr_size = 1, *_arr_size = &arr_size;
	char ter_str[] = "($) ", *lineptr = NULL, **args;
	int semi_seen = 0, *_semi_seen = &semi_seen;

	if ((*envi == NULL) && (*env == NULL))
	{
		_setup_env_nodes(env);
		_setup_env(env, &envi);
	}
	if (isatty(STDIN_FILENO) == 1)
		dprintf(STDOUT_FILENO, "%s", ter_str);
	while ((size = _getline(&lineptr, &_semi_seen)) > 0)
	{
		if (size > 1)
		{
			args = _strtok(lineptr, &_arr_size);
			if ((args == NULL) && (isatty(STDIN_FILENO) == 1))
				dprintf(STDOUT_FILENO, "%s", ter_str);
			else if ((args != NULL) && (args[0][0] != 0))
				_cmd_check(ter_str, args, av, envi, status,
				&_arr_size, lineptr, &_semi_seen, env);
			else if (isatty(STDIN_FILENO) == 1)
				dprintf(STDOUT_FILENO, "%s", ter_str);
			if (args != NULL)
				_free(args);
			free(lineptr);
		}
		else if (size == 1)
		{
			if (isatty(STDIN_FILENO) == 1)
				dprintf(STDOUT_FILENO, "%s", ter_str);
			free(lineptr);
		}
	}
	if (isatty(STDIN_FILENO) == 1)
		dprintf(STDOUT_FILENO, "\n");
	free(lineptr);
}
