#include "header.h"

// function pointers
t_array* init_t_array(int size);
char* init_str(int size);
char** init_string_arr(int size);
void free_t_array(t_array* tokens);
void free_string_arr(char** string_array);
int simple_exit_success(char** env);
int simple_exit_failure(char** env, t_array *tokens);

// testing functions
void print_t_array(t_array* tokens);
void print_array(char** array);