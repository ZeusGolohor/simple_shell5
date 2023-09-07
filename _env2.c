#include "main.h"

int _setenv(env_t ***env, char **args, char ***envi)
{
	env_t *temp;
	int seen = 0;
	env_t *new_node;
	char *separator = "=";

	if ((args[1] == NULL) || (args[2] == NULL))
	{
		dprintf(STDOUT_FILENO, "usage: setenv VARIABLE VALUE\n");
		dprintf(STDOUT_FILENO, "($) ");
		return (-1);
	}
	if (**env != NULL)
		temp = **env;
	while (temp->next != NULL)
	{
		if ((args[1] != NULL) && (strcmp(temp->var, args[1]) == 0))
		{
			seen = 1;
			printf("%s\n", temp->var_n_val);
		}
		temp = temp->next;
	}
	printf("%s\n", args[1]);
	if ((temp->next == NULL) && (seen == 0))
	{
		printf("env not found, creeating it now\n");
		new_node = malloc(sizeof(env_t));
		if (new_node == NULL)
			return (-1);
		new_node->var = malloc(sizeof(char) * (strlen(args[1] + 1)));
		new_node->val = malloc(sizeof(char) * (strlen(args[2] + 1)));
		new_node->var_n_val = malloc(sizeof(char) * (strlen(args[1]) + strlen(separator) + strlen(args[2]) + 1));
	if ((new_node->var == NULL) || (new_node->val == NULL) || (new_node->var_n_val == NULL))
		return (-1);
	new_node->var[0] = '\0';
	new_node->val[0] = '\0';
	new_node->var_n_val[0] = '\0';
	strcat(new_node->var_n_val, args[1]);
	strcat(new_node->var_n_val, separator);
	strcat(new_node->var_n_val, args[2]);
	new_node->next = NULL;
	_add_env(*env, new_node);
/*	_free_env_b_head(*envi);*/
	_setup_env(*env, envi); 
	}
	printf("printing new env\n");
	_print_env(*env);
	return (0);
}

int _print_env2(char **env)
{
	int i;

	if (*env == NULL)
		return (-1);
	i = 0;
	while (env[i] != NULL)
	{
		dprintf(STDOUT_FILENO, "%s\n", env[i]);
		++i;
	}
	return (0);
}
