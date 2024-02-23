#include <stdio.h>
#include <stdlib.h>
#include "../inc/executer.h" 
#include "../inc/parse.h"
#include "../inc/memory.h"
#include "../inc/helper.h"
#include "../inc/builtins.h" 
#include "../inc/sig_handler.h" 
#include "../inc/mempool.h"

int execute_cmd(t_array* tokens, char** my_env) 
{
    if (!tokens) { return EXIT_FAILURE; }

    // execute builtin commands
    int status;
    status = execute_builtin(tokens, my_env);

    // execute binary commands
    if (!status) {
        if (execute_binary(tokens, my_env)) { return EXIT_FAILURE; }
    }

    return EXIT_SUCCESS;
}

int execute_builtin(t_array* tokens, char** my_env)   
{
    token_function_map mappings[] = {
        { "echo", zshhy_echo },
        { "cd", zshhy_cd },
        { "setenv", zshhy_setenv },  
        { "unsetenv", zshhy_unsetenv }, 
        { "env", zshhy_env },
        { "exit", zshhy_exit },  
        { "pwd", zshhy_pwd },
        { "which", zshhy_which }
    };

    int num_mappings = sizeof(mappings) / sizeof(mappings[0]);

    int i = 0;

    while (i < num_mappings) {
        if (my_strcmp(mappings[i].token, tokens->array[0]) == 0) {
            mappings[i].function(tokens, my_env);
            return 1;
        }
        i++;
    }
    
    return 0;
}

int execute_binary(t_array* tokens, char** my_env) 
{
    memory_pool_t pool;
    initialize_pool(&pool);
    char *path_options = allocate(&pool);
    char *path = allocate(&pool);
    char **path_ptr;

    // check for binary path
    if (!(path_ptr = binary_path(&tokens, my_env, path_options, &path))) { 
        if (!(path_ptr = custom_binary_path(&tokens, &path))) {
            my_putstrerr("Error executing command: No such file\n");
            print_usage();
            return EXIT_FAILURE;
        }
    }

    pid_t pid;
    int status;
    pid = fork();
    
    if (pid == 0) { // Child process
        if (execve(path, tokens->array, my_env) == -1) { 
            my_putstrerr("execve\n"); 
            return EXIT_FAILURE;
        } 
        return EXIT_FAILURE;
    } else if (pid < 0) {   // Error forking
        perror("fork");
        return EXIT_FAILURE;
    } else {    // Parent process
        waitpid(pid, &status, WUNTRACED);

        if (WIFEXITED(status)) { return WEXITSTATUS(status); }  // Child exited normally
        else if (WIFSIGNALED(status)) {     // Child terminated by a signal
            int term_sig = WTERMSIG(status);
            signal_handler(term_sig);
            return EXIT_FAILURE; 
        }
    }
    return EXIT_SUCCESS;
}


char **binary_path(t_array** tokens, char** my_env, char *path_opt, char **path)
{
    // get path from environment
    if (!my_env) { return NULL; }
    path_opt = get_env_variable("PATH", my_env);            
    if (!path) { return NULL; }

    // create env directory
    t_array* cmd_directory = NULL;
    char separator = ':';
    if (!(cmd_directory = tokenize(&path_opt, separator))) { return NULL; }   

    // check directory for path
    int i = 0;
    struct stat sb;

    while (i < cmd_directory->size) {
        char* slash = "/";
        my_strcpy(*path, cmd_directory->array[i]);
        my_strcat(*path, slash);
        my_strcat(*path, (*tokens)->array[0]); 

        if ((stat(*path, &sb)) == 0) 
        {
            cmd_directory->free_t_array(cmd_directory);
            return path;
        }
        i++;
    }

    // free directory
    cmd_directory->free_t_array(cmd_directory);

    return NULL;
}

char **custom_binary_path(t_array** tokens, char **path) 
{
    int len = my_strlen((*tokens)->array[0]);
    my_strncpy(*path, (*tokens)->array[0], len + 1);

    if (!path) { return NULL; }

    // check path
    struct stat sb;

    if ((stat(*path, &sb)) == 0) {
        return path;
    }

    return NULL;
}

char *get_env_variable(char* name, char** my_env)  
{
    int i = 0;
    int name_len = my_strlen(name);

    while (my_env[i]) {
        if (my_strncmp(name, my_env[i], name_len) == 0) {
            char* value = my_env[i] + name_len + 1; 
            return value;
        }
        i++;
    }
    
    return NULL;
}
