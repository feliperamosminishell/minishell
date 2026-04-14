This project has been created as part of the curriculum of 42 by juan-her, goramos-

# Minishell

## Description

Minishell is a simplified implementation of a Unix shell, developed as
part of the 42 curriculum. The goal of this project is to understand how
command interpreters work by recreating essential features of a shell
such as Bash.

This project focuses on: - Parsing user input - Executing commands -
Managing processes and file descriptors - Handling signals -
Implementing environment variables and built-in commands

Minishell provides a hands-on introduction to system programming
concepts such as process creation (`fork`), program execution
(`execve`), and inter-process communication (`pipe`).

------------------------------------------------------------------------

## Features

-   Command execution (with absolute or relative paths)
-   Environment variable expansion (`$VAR`)
-   Built-in commands:
    -   `echo`
    -   `cd`
    -   `pwd`
    -   `export`
    -   `unset`
    -   `env`
    -   `exit`
-   Pipes (`|`)
-   Input/Output redirections:
    -   `<` input redirection
    -   `>` output redirection
    -   `>>` append output
    -   `<<` heredoc
-   Signal handling (Ctrl+C, Ctrl+D, Ctrl+)
-   Error management and exit codes

------------------------------------------------------------------------

## Instructions

### Requirements

-   Unix-based operating system (Linux or macOS)
-   `gcc` compiler
-   `make`

### Compilation

Clone the repository and compile the project using:

``` bash
make
```

This will generate the executable: minishell

### Execution

Run the shell with:

``` bash
./minishell
```

### Cleaning

``` bash
make clean
```

``` bash
make fclean
```

``` bash
make re
```

------------------------------------------------------------------------

## Usage Examples

``` bash
$ echo Hello World
Hello World

$ ls -l | grep minishell

$ export NAME=42
$ echo $NAME
42

$ cat < input.txt > output.txt

$ exit
```

------------------------------------------------------------------------

## Technical Decisions

-   Lexer & Parser for structured input
-   fork/execve execution model
-   Pipe handling with dup2
-   Careful memory management
-   Custom signal handling

------------------------------------------------------------------------

## Resources

### Documentation & References

-   The Linux Programming Interface -- Michael Kerrisk
-   Advanced Programming in the UNIX Environment -- W. Richard Stevens
-   GNU Bash Manual: https://www.gnu.org/software/bash/manual/
-   POSIX Standard: https://pubs.opengroup.org/onlinepubs/9699919799/

### Tutorials

-   https://linuxhint.com/write-simple-shell-c/
-   https://brennan.io/2015/01/16/write-a-shell-in-c/

### Use of AI

AI tools were used for: - Understanding system calls - Debugging -
Documentation assistance

All implementation decisions were reviewed manually.

------------------------------------------------------------------------
