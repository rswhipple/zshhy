#include "../inc/parse.h" 
#include "../inc/memory.h"  
#include "../inc/helper.h" 

t_array* parse_cmd(char* cmd)   
{
    // create tokens
    t_array* tokens = NULL;
    char separator = ' ';
    if (!(tokens = tokenize(&cmd, separator))) { return NULL; }    

    return tokens;
}

t_array* tokenize(char** src, char separator) 
{
    t_array* tokens = NULL;
    int status;

    // create tokens
    int num_tokens = count_args(*src, separator);
    
    // // handle edge case all spaces
    if (!num_tokens) { return NULL; }

    // initialize token array and run lexer
    tokens = init_t_array(num_tokens);  
    if ((status = lexer(&tokens, *src, separator, num_tokens))) { 
        free_t_array(tokens);
        return NULL; 
    }

    return tokens;
}

int lexer(t_array** tokens, char* src, char separator, int size)  
{
    if (!separator) { separator = ' '; }
    int i = 0, j = 0, counter = 0;
    char *temp = src;

    while (j < size && src[i]) {
        // skip initial spaces
        while (src[i] == separator || src[i] == '\t') { i++, temp++; }

        // count length of arg
        if (src[i]) {
            while (src[i] != separator && src[i] != '\t' && src[i] != '\n' && src[i]) {
                i++, counter++;
            }
            counter++;

            if (*temp == '\n') { break; }   // if last string is '\n', skip
            // allocate memory and copy string
            (*tokens)->array[j] = init_str(counter);
            my_strncpy((*tokens)->array[j], temp, counter);
            (*tokens)->size += 1;
            i++, j++;
            temp += counter, counter = 0;
        }
    }

    return EXIT_SUCCESS;
}

int count_args(char* src, char separator)  
{
    if (!separator) { separator = ' '; }
    char num_tokens = 0;
    char *temp = src;

    while (*temp == separator || *temp == '\t' ) {  // skip initial spaces
        temp++; 
    }
    
    if (!*temp || *temp == '\n') {  // handle all spaces edge case
        return num_tokens; 
    }

    while (*temp) { // count spaces between args
        if (*temp == separator || *temp == '\t') {
            while (*temp == separator || *temp == '\t' ) {
                temp++;
            }
            num_tokens++;
        }
        temp++;
    }
    num_tokens++;

    return num_tokens;
}

