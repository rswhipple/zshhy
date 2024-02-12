#include <stdlib.h>
#include "../inc/header.h" 
#include "../inc/helper.h" 
#include "../inc/parse.h" 
#include "../inc/executer.h" 
#include "../inc/memory.h" 

int main(int ac, char** av, char** env)
{
    // Run shell
    if (zshhy_cli(ac, av, env)) { 
        return EXIT_FAILURE; 
    }

    return EXIT_SUCCESS;
}

int zshhy_cli(int ac, char** av, char** env) 
{ 
    t_array* toks = NULL;
    char** my_env = create_env(env);

    // Execute commands (if any) from initial program call
    if (ac > 1) {
        if ((my_strcmp(av[1], "quit") == 0)) \
                { return simple_exit_success(my_env); }
        if (ac == 2) {
            toks = parse_cmd(av[1]); 
            if (execute_cmd(toks, my_env)) \
                    { return simple_exit_failure(my_env, toks); }
            toks->free_t_array(toks); 
        }
        else if (ac > 2) {
            char *cmd = format_command_str(ac, av);
            toks = parse_cmd(cmd);
            free(cmd);

            if (execute_cmd(toks, my_env)) \
                    { return simple_exit_failure(my_env, toks); }
            toks->free_t_array(toks);
        }
    }

    // Run loop
    if (zshhy_loop(my_env)) { return EXIT_SUCCESS; }
    free_string_arr(my_env);
    
    return EXIT_SUCCESS;

}

int zshhy_loop(char** my_env) 
{
    t_array* tokens = NULL;
    char* cmd = NULL;

    while (1) {
        // display_prompt();        // FIX PROMPT ISSUE, TALK TO GAETAN
        cmd = get_cmd();
        if (!cmd || cmd[0] == '\0') { return EXIT_SUCCESS; } // handles EOF
        if ((my_strcmp(cmd, "quit\n") == 0)) {
            free(cmd);  
            return EXIT_SUCCESS;
        }
        
        tokens = parse_cmd(cmd); 
        free(cmd);
        if (!tokens) { continue; }

        if (execute_cmd(tokens, my_env)) \
                { return simple_exit_failure(my_env, tokens); }
        tokens->free_t_array(tokens); 
    }

    return EXIT_SUCCESS;
}

char **create_env(char** env) 
{
    int size = 0;

    while (env[size]) {
        size++;
    }
    int buffer_size = size + 10;
    char** my_env = init_string_arr(buffer_size);

    int i = 0;

    while (i < size) {
        int len = my_strlen(env[i]) + 1;
        my_env[i] = malloc(sizeof(char) * len);
        my_strncpy(my_env[i], env[i], len);
        i++;
    }

    return my_env;
}

void display_prompt()
{
    my_putstr("zshhy> ");
    // fflush(stdout);
}

char* get_cmd(void) 
{
    char* cmd = NULL;
    size_t len = 0;
    ssize_t read;
    
    read = getline(&cmd, &len, stdin);

    if (read == -1) {
        return NULL;
    }

    return cmd;
}

void print_my_env(char** my_env)
{
    int i = 0;

    while (my_env[i]) {
        my_putstr(my_env[i]);
        my_putstr("\n");
        i++;
    }
}

char *format_command_str(int ac, char** av)
{
    int i = 1;
    int len = my_strlen(av[i]) + 1;
    char* cmd = init_str(len);
    my_strcpy(cmd, av[i]);
    i++;
    while (i < ac) {
        cmd = realloc(cmd, sizeof(char) * \
                (my_strlen(cmd) + my_strlen(av[i]) + 2));
        my_strcat(cmd, " ");
        my_strcat(cmd, av[i]);
        i++;
    }

    return cmd;
}

