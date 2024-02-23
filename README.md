# Zshhy
A custom shell in C.

Zshhy is a UNIX command interpreter that can handle both builtin and binary functions. 

Only basic command lines are executed in the shell; no pipes, redirections or any other advanced features. 

## Description
Binary functions (executables) are those found in the path, as indicated in the PATH variable. If an executable cannot be found, an error message is displayed and than the prompt is shown again. Errors are dealt with and the appropriate message is displayed on the error output. 

The following builtins are implemented: echo, cd, setenv, unsetenv, env, exit, pwd and which.

Demonstrated knowledge:

- **UNIX System Calls**: Utilized system calls such as `fork()`, `exec()`, and `wait()` to execute binary functions, showcasing an understanding of process creation and management in UNIX-like systems.

- **Environment Variable Management**: Implemented functionality to modify environment variables (`setenv`, `unsetenv`) and access them (`env`), demonstrating knowledge of how shells interact with the operating system environment as well as how they acccess and execute commands.

- **Memory Management**: Integrated a custom memory pool for efficient memory allocation and deallocation, highlighting advanced memory management techniques and reducing the risk of memory leaks in long-running applications.


## How To Use
Within the project folder, compile the program via the command line interface using the make command:
```
> make
```
Run zshhy:
```
./zshhy
```
And use zshhy as you would zsh:
```
zshhy > <builtin or binary function name> <flags>
```

## Requirements
Qwasar allows for a only a limited selection of functions to be used in the program. All other functionality has been custom built.

Authorized functions:
* malloc, free, exit, opendir, readdir, closedir, getcwd, chdir
* fork, stat, lstat, fstat, open, close, getline
* read, write, execve, isatty, wait, waitpid
* wait3, wait4, signal, kill, getpid, strerror, perror.


### The Core Team
Solo project:
Rebecca Whipple Silverstein

<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
