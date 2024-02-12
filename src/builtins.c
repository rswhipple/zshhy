#include "../inc/builtins.h" 
#include "../inc/helper.h" 
#include "../inc/parse.h" 
#include "../inc/memory.h" 
#include "../inc/mempool.h" 
#include "../inc/executer.h"

void zshhy_echo(t_array* tokens, char** my_env) 
{
    // check for required args
    if (!my_env) { return; }
    if (tokens->size < 2) \
            { my_putstrerr("zshhy: expected argument to \"echo\"\n"); } 
    else {
        // special characters
        if (tokens->array[1][0] == '$') {
            char* name = tokens->array[1] + 1;
            print_env_variable(name, my_env);
            return;
        }

        // write to stdout
        int i = 1;

        while (i < tokens->size - 1) {
            my_putstr(tokens->array[i]);
            my_putstr(" ");
            i++;
        }
        my_putstr(tokens->array[i]);
        my_putstr("\n");
    } 
} 

void print_env_variable(char* name, char** my_env) 
{
    int i = 0;
    int name_len = my_strlen(name);

    while (my_env[i]) {
        if (my_strncmp(name, my_env[i], name_len) == 0) {
            my_putstr(my_env[i] + name_len + 1);
            my_putstr("\n");
        }
        i++;
    }
    
}

void zshhy_cd(t_array* tokens, char** my_env)
{
    // initiate static variable
    static char previous_dir[MAX_PATH] = "";
    char current_dir[MAX_PATH];

    // check for required args
    if (!my_env) { return; }
    if (tokens->size < 2) {
        my_putstrerr("zshhy: expected argument to \"cd\"\n");
    } 
    else {
        // save current directory to buf
        if (!getcwd(current_dir, MAX_PATH)) {
            perror("getcwd() error");
            return;
        }

        if (strcmp(tokens->array[1], "-") == 0) {
            if (previous_dir[0] == '\0') {
                my_strncpy(previous_dir, current_dir, my_strlen(current_dir) + 1);
                perror("No previous directory stored");
                return;
            }
            if (chdir(previous_dir) != 0) {
                perror("chdir() error");
                return;
            }

        }
        else {
            if (chdir(tokens->array[1]) != 0) {
                my_strncpy(previous_dir, current_dir, my_strlen(current_dir)+1);
                perror("zshhy");
                return;
            }
        }
        my_strncpy(previous_dir, current_dir, my_strlen(current_dir) + 1);
    }
}

void zshhy_pwd(t_array* tokens, char** my_env)
{
    if (!my_env) { return; }
    if (!tokens) {
        my_putstrerr("zshhy: expected argument\n");
        return;
    }

    char buf[MAX_PATH] = "";

    if (!getcwd(buf, MAX_PATH)) {
        perror("zshhy:");
        return;
    }
    my_putstr(buf);
    my_putstr("\n");
}

void zshhy_setenv(t_array* tokens, char** my_env) 
{
    // check for required args
    if (tokens->size < 2) {
        my_putstrerr("zshhy: expected argument to \"setenv\"\n");
    } 
    else {
        // tokenize env variable
        int i = 0;
        int len = my_strlen(tokens->array[1]) + 1;
        char* env_variable = init_str(len);
        my_strncpy(env_variable, tokens->array[1], len);
        t_array* key_value = tokenize(&tokens->array[1], '=');
        int name_len = my_strlen(key_value->array[0]);

        // check for existing env variable
        while (my_env[i] != NULL) {
            if (my_strncmp(key_value->array[0], my_env[i], name_len) == 0 && 
                    my_env[i][name_len] == '=') {
                // if env exists, replace value and exit function
                my_env[i] = env_variable;
                return;
            }
            i++;
        }
        key_value->free_t_array(key_value);

        // if env variable does not exist, create new variable
        my_env[i] = env_variable;
        my_env[i + 1] = NULL;
    }
}

void zshhy_unsetenv(t_array* tokens, char** my_env)
{
    // check for required args
    if (tokens->size < 2) {
        my_putstrerr("zshhy: expected argument to \"unsetenv\"\n");
    } 
    else {
        int i = 0;
        int name_len = my_strlen(tokens->array[1]);
        // free and set variable to NULL
        while (my_env[i]) {
            if (my_strncmp(tokens->array[1], my_env[i], name_len) == 0) {
                free(my_env[i]);
                my_env[i] = NULL;
            }
            i++;
        }
    }
}

void zshhy_env(t_array* tokens, char** my_env)
{
    // write to stdout line by line
    int i = 0;
    if (tokens->size < 2) {
        while (my_env[i]) {
            my_putstr(my_env[i]);
            my_putstr("\n");
            i++;
        }
    }
}

void zshhy_exit(t_array* tokens, char** my_env)
{
    if (!my_env) { return; }
    if (tokens->size >= 2) {
        tokens->free_t_array(tokens);
        exit(EXIT_FAILURE);
    } 
    tokens->free_t_array(tokens);
    exit(EXIT_SUCCESS);
}

void zshhy_which(t_array* tokens, char** my_env)
{
    // check for required args
    if (tokens->size < 2) {
        my_putstrerr("zshhy: expected argument to \"which\"\n");
    } 
    else {
        if(!(which_builtin(tokens))) {
            which_binary(tokens, my_env);
        }
    }
    
}

int which_builtin(t_array* tokens)
{
    char* builtins[] = {
        "echo",
        "cd",
        "setenv",
        "unsetenv",
        "env",
        "exit",
        "pwd", 
        "which"
    };

    int num_builtins = 8;

    int i = 0;

    while (i < num_builtins) {
        if (my_strcmp(builtins[i], tokens->array[1]) == 0) {
            char message[100];
            my_strcpy(message, tokens->array[1]);
            my_strcat(message, ": zshhy built-in command\n");
            my_putstr(message);
            return 1;
        }
        i++;
    }

    return 0;
}

int which_binary(t_array* tokens, char** my_env)
{
     // get path from environment
    if (!my_env) { return 0; }
    char* path = get_env_variable("PATH", my_env);            
    if (!path) { return 0; }

    // create tokens
    t_array* cmd_directory = NULL;
    char separator = ':';

    if (!(cmd_directory = tokenize(&path, separator))) { return 0; }   

    // construct full path and check directory for path
    int i = 0;
    struct stat sb;

    while (i < cmd_directory->size) {
        char* full_path = init_str(MAX_PATH); 
        char* slash = "/";
        my_strcpy(full_path, cmd_directory->array[i]);
        my_strcat(full_path, slash);
        my_strcat(full_path, tokens->array[1]); 

        if ((stat(full_path, &sb)) == 0) {
            my_putstr(full_path);
            my_putstr("\n");
            free(full_path);
            cmd_directory->free_t_array(cmd_directory);
            return 1;
        }
        free(full_path);
        i++;
    }

    // free directory
    cmd_directory->free_t_array(cmd_directory);

    return 0;   
}