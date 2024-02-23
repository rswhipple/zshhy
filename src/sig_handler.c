#include "../inc/sig_handler.h"
#include "../inc/helper.h"

void signal_handler(int signal_num)
{
    if (signal_num == 1) {
        my_putstrerr("general error\n");
    }
    else if (signal_num == 2) {
        my_putstrerr("misuse of shell builtins\n");
    }
    else if (signal_num == 127) {
        my_putstrerr("command not found\n");
    }
    else if (signal_num == 11 || signal_num == 139) {
        my_putstrerr("segmentation fault\n");
    }
    else if (signal_num < 0) {
        my_putstrerr("status out of range\n");
        
    }
    else if (signal_num > 255) {
        my_putstrerr("status out of range\n");
    }
}

