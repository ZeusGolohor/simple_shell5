#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
/**
 * struct env_s - env structure.
 * @var_n_val: holds VARIABLE=value.
 * @var: holds VARIABLE.
 * @val: holds value.
 * @next: holds a pointer to the next env node.
 *
 * Description: env structure for building a
 * linked list of environment variables.
 */
typedef struct env_s
{
char *var_n_val;
char *var;
char *val;
struct env_s *next;
} env_t;
extern env_t **_h_env;
extern char **_h_envi;
extern char **environ;
void _shell(int, char **, char **, int **, env_t **);
void _fork(char *, char **, char **, char **,
int **, char *, int **, env_t **);
ssize_t _getline_check(char *);
char **_strtok(char *, ssize_t **);
void _free(char **);
void _cmd_check(char *, char **, char **, char **,
int **, ssize_t **, char *, int **, env_t **);
ssize_t _getline(char **, int **);
int _setup_env_nodes(env_t **);
int _setup_env(env_t **, char ***);
int _add_env(env_t **_env, env_t *new_env_node);
int _print_env(env_t **);
int _print_env2(char **);
int _free_env_nodes(env_t **);
int _free_env(char **);
int _free_env_b_head(char **);
void _ctrl_c_handler(int);
int _setenv(env_t ***, char **, char ***);
#endif
