#ifndef _ZSHHY_CLI_H
#define _ZSHHY_CLI_H

#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>  // open()

// macros
#define MAX_LINE 512

// structs
typedef struct t_array_s {
    int size;
    char** array;

    void (*free_t_array)(struct t_array_s* tokens);
    void (*print_t_array)(struct t_array_s* tokens);
} t_array;

// function prototypes
int zshhy_cli(int ac, char** av, char** env);
int zshhy_loop(char** env);
char **create_env(char** env);
void display_prompt(void);
char *get_cmd(void);
void print_my_env(char** my_env);
char *format_command_str(int ac, char** av);

#endif
