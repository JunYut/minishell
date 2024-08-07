Raw:	`cat -e << eof | grep lol -v > output.txt` \
Token:	`cmd argv << delim | cmd argv > file` \
Parse:	`[cmd1] [<< delim] [|] [cmd2] [> file]` \
Exec:	`[<< delim] [|] [> file] [cmd1] [cmd2]` \
Output:

	heredoc:
	> hello world lol
	> how
	> are you
	> lol
	> I am
	> doing well lol
	> lol lol lol
	> eof
---
	output.txt:

	how$
	are you$
	I am$
