# minishell

A minimal Bash clone written in C

## Features

- Interactive prompt with command history (up/down arrows)
- Builtins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- External commands, with and without pipelines (`|`)
- Input/output redirections (`<`, `>`, `>>`) and heredocs (`<<`)
- Single and double quotes, environment variable expansion (`$VAR`, `$?`)
- Basic syntax checking and signal handling for `Ctrl-C` and `Ctrl-\`

## Build and run

Requires `make`, `gcc`, and the readline development headers. On Linux, the system readline library is used; on macOS, the bundled copy in `lib/lib/readline` is used.

```sh
make            # build ./minishell
./minishell     # start the shell
make fclean     # remove the binary
make re         # rebuild from scratch
```

## Usage examples

```sh
minishell > echo hello world

minishell > export NAME=Ali
minishell > echo "Hello, $NAME"

minishell > ls -l | grep minishell > output.txt

minishell > cat << EOF
heredoc >> first line
heredoc >> EOF

minishell > exit
```
