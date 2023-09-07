#include "main.h"

/**
 * _cmd_check - A function used to check shell commands before they are run.
 * @ter_str: the string to be printed at the terminal.
 * @args: modified argumants passed to the program.
 * @av: unmodified arguments passed to the program.
 * @env: the OS environment variables.
 *
 * Return: void.
 */
void _cmd_check(char *ter_str, char **args, char **av, char **envi, int **status, __attribute__((unused)) ssize_t **arr_size, char *lineptr, int **semi_seen, env_t **env)
{
	long number;
	char *str;

	if ((args[0][0] == 'e') && (args[0][1] == 'x') && (args[0][2] == 'i') && (args[0][3] == 't'))
	{
		_free_env(envi);
		_free_env_nodes(env);
		if ((args[1] != NULL) && ((args[1][0] < '0') || args[1][0] > '9'))
		{
			dprintf(STDERR_FILENO, "%s: %d: exit: Illegal number: %s\n",
		av[0], 1, args[1]);
			free(lineptr);
			_free(args);
			exit(2);
		}
		else if ((args[1] != NULL) && (atoi(args[1]) < 0))
		{
			dprintf(STDERR_FILENO, "%s: %d: exit: Illegal number: %d\n",
		av[0], 1, atoi(args[1]));
			free(lineptr);
			_free(args);
			exit(2);
		}
		else if ((args[1] != NULL) && ((args[1][0] >= '0') || args[1][0] <= '9'))
		{
			number = strtol(args[1], &str, 10);
			free(lineptr);
			_free(args);
			exit(number);
		}
		if (**status == 512)
		{
			**status = 0;
			free(lineptr);
			_free(args);
			exit(2);
		}
		else
		{
			free(lineptr);
			_free(args);
			exit(0);
		}
	}
	else if ((args[0][0] == '/') && (args[0][1] == 'b') && (args[0][2] == 'i') && (args[0][3] == 'n') && (args[0][4] == '/') && (args[0][5] == 'e') && (args[0][6] == 'n') && (args[0][7] == 'v'))
	{
	/*	_setup_env_nodes(envi);*/
		_print_env(env);
		printf("\nprinting env char\n");
		_print_env2(envi);
		if (isatty(STDIN_FILENO) == 1)
			dprintf(STDOUT_FILENO, "%s", ter_str);
	}
	else if ((args[0][0] == 's') && (args[0][1] == 'e') && (args[0][2] == 't') && (args[0][3] == 'e') && (args[0][4] == 'n') && (args[0][5] == 'v'))
	{
		_setenv(&env, args, &envi);
	}
	else
		_fork(ter_str, args, av, envi, status, lineptr, semi_seen, env);
}
