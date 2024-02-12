# Zshhy
A custom shell in C.

## Task
Create a UNIX command interpreter that can handle both builtin and binary functions. 

Only basic command lines are to be executed; no pipes, redirections or any other advanced features. 

## Requirements
Authorized functions:
* malloc, free, exit, opendir, readdir, closedir, getcwd, chdir
* fork, stat, lstat, fstat, open, close, getline
* read, write, execve, isatty, wait, waitpid
* wait3, wait4, signal, kill, getpid, strerror, perror.

Multiline macros are forbidden.
Macros with logic (while/if/variables/...) are forbidden.

## Description
Binary functions (executables) are those found in the path, as indicated in the PATH variable.

If an executable cannot be found, an error message is displayed and than the prompt is shown again. Errors are dealt with and the appropriate message is displayed on the error output. 

The following builtins are implemented: echo, cd, setenv, unsetenv, env, exit, pwd and which.


## Installation
Compile the program via the command line interface using the make command:
```
> make
```

## Usage
```
./zshhy <builtin or binary function name> <flags>
```

### The Core Team
Solo project:
rswhipple (Rebecca Whipple Silverstein)

<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
