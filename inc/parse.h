#include "header.h"

// function prototypes
t_array* parse_cmd(char* cmd);
t_array* tokenize(char** src, char separator);
int lexer(t_array** tokens, char* src, char separator, int size);
int count_args(char* src, char separator);
