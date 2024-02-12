#ifndef _BUILTINS_H
#define _BUILTINS_H
#include "header.h"

// structs
typedef void (*callback_function)(t_array* tokens, char** my_env);

typedef struct {
    char token[25];
    callback_function function;
} token_function_map;


// function prototypes
void zshhy_echo(t_array* tokens, char** my_env);
void print_env_variable(char* name, char** my_env);
void zshhy_cd(t_array* tokens, char** my_env);
void zshhy_setenv(t_array* tokens, char** my_env);
void zshhy_unsetenv(t_array* tokens, char** my_env);
void zshhy_env(t_array* tokens, char** my_env);
void zshhy_exit(t_array* tokens, char** my_env);
void zshhy_pwd(t_array* tokens, char** my_env);
void zshhy_which(t_array* tokens, char** my_env);
int which_builtin(t_array* tokens);
int which_binary(t_array* tokens, char** my_env);

#endif