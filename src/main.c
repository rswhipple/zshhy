#include <stdlib.h>
#include "../inc/header.h" 

int main(int ac, char** av, char** env)
{
    // Run shell
    if (zshhy_cli(ac, av, env)) { 
        return EXIT_FAILURE; 
    }

    return EXIT_SUCCESS;
}

