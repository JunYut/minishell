Raw: `cat -e << eof | grep lol -v > output.txt`
Token: `cmd argv << delim | cmd argv > file`
Parse: `[cmd1] [<< delim] [| cmd2] [> file]`
Exec: heredoc -> pipe -> redout -> cmd1 -> cmd2