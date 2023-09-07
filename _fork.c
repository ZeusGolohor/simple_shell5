#include "main.h"

/**
 * _fork - A function used to execute in a command in a chid process.
 * @ter_str: the string to be displayed at the terminal.
 * @args: modified commands passed to the program.
 * @av: unmodified arguments passed to the program.
 * @env: the environment variables of the OS.
 *
 * Return: void.
 */
void _fork(char *ter_str, char **args, char **av, char **envi, int **status, char *lineptr, int **semi_seen, env_t **env)
{
	pid_t cid;
	int sta;

	if (access(args[0], F_OK) == 0)
	{
		cid = fork();
		if (cid == 0)
		{
			execve(args[0], args, envi);
		}
		else
		{
			waitpid(cid, &sta, 0);
			if (sta == 512)
			{
				**status = 512;
				_free(args);
				free(lineptr);
				_shell(0, av, envi, status, env);
				_free_env(envi);
				_free_env_nodes(env);
				exit(2);
			}
			if ((isatty(STDIN_FILENO) == 1) && (**semi_seen != 1))
				dprintf(STDOUT_FILENO, "%s", ter_str);
			if (**semi_seen == 1)
				**semi_seen = 0;
		}
	}
	else
	{
	/*	printf("%s: No such file or directory\n", av[0]);*/
		dprintf(STDERR_FILENO, "%s: %d: %s: not found\n", av[0], 1, args[0]);
		_free(args);
		free(lineptr);
		_shell(0, av, envi, status, env);
		_free_env(envi);
		_free_env_nodes(env);
		exit(127);
		if (isatty(STDIN_FILENO) == 1)
			dprintf(STDOUT_FILENO, "%s", ter_str);
	}
}
