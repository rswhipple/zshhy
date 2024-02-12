#ifndef EXECUTER_H
#define EXECUTER_H

#include "header.h"
#include "builtins.h"
#include "mempool.h" 

// macros
#define MAX_PATH 512

// function prototypes
int execute_cmd(t_array* tokens, char** env);
int execute_builtin(t_array* tokens, char** env);
int execute_binary(t_array* tokens, char** env);
char **binary_path(t_array** tokens, char** my_env, char* path_options, char **path);
char **custom_binary_path(t_array** tokens, char** path);
char *get_env_variable(char* name, char** my_env);

#endif
