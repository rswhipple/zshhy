#include "../inc/memory.h"

t_array* init_t_array(int size)  
{
    t_array* new_array = malloc(sizeof(t_array));
    new_array->array = malloc(sizeof(char*) * size + 2); // extra space for setenv
    new_array->size = 0;
    new_array->free_t_array = free_t_array;  
    new_array->print_t_array = print_t_array;

    for (int i = 0; i < size; i++) { new_array->array[i] = NULL; }

    return new_array;
}

char* init_str(int size)  
{
    char* str = malloc(sizeof(char) * size + 1);

    for (int i = 0; i < size + 1; i++) { str[i] = '\0'; }

    return str;
}

char** init_string_arr(int size)
{
    char** new_array = malloc(sizeof(char*) * (size + 1));

    for (int i = 0; i <= size; i++) { new_array[i] = NULL; }

    return new_array;
}

void free_t_array(t_array* tokens)
{ 
    int i = 0;
    while (i < tokens->size) {
        free(tokens->array[i]) ;
        i++;
    }
    
    free(tokens->array);
    free(tokens);
}

void free_string_arr(char** string_array)
{
    int i = 0;
    while (string_array[i]) {
        free(string_array[i]);
        i++;
    }
    
    free(string_array);

}
 
void print_t_array(t_array* tokens)
{
    int i = 0;

    while (i < tokens->size) {
        printf("tokens->array[%i] = %s\n", i, tokens->array[i]);
        i++;
    }
}

void print_array(char** array)
{
    int i = 0;

    while (array[i]) {
        printf("char* array[%i] = %s\n", i, array[i]);
        i++;
    }
}

int simple_exit_success(char** env)
{
    free_string_arr(env);
    return 0;
}

int simple_exit_failure(char** env, t_array *tokens)
{
    tokens->free_t_array(tokens);
    free_string_arr(env);
    return 1;
}

