**Raw:**	`cat -e << eof | grep lol -v > output.txt` \
**Token:**	`cmd argv << delim | cmd argv > file` \
**Exec:**	`[cmd1] [<< delim] [|] [cmd2] [> file]` \
**Seq:**	`[<< delim] [|] [> file] [cmd1] [cmd2]` \
**Output:**
```
heredoc:
	> hello world lol
	> how
	> are you
	> lol
	> I am
	> doing well lol
	> lol lol lol
	> eof
```
```
	output.txt:

	how$
	are you$
	I am$
```

**Raw:**	`cat not-exist && echo should not print this || echo interesting` \
**Token:**	`cmd argv && cmd argv || cmd argv` \
**Exec:**	`[cmd1] [&& cmd2] [|| cmd3]` \
**Seq:**	`[cmd1] [&& cmd2] [|| cmd3]` \
**Output:**
```
cat: not-exist: No such file or directory
interesting
```

**Raw:**	`env | grep -E VSCODE && env | cat -e not_exist || echo working as intended > output.txt` \
**Token:**	`cmd | cmd argv && cmd | cmd argv || cmd argv > file` \
**Exec:**	`[cmd1] [|] [cmd2] [&& cmd3] [|] [cmd4] [|| cmd5] [> file]` \
**Seq:**	`[|] [|] [> file] [cmd1] [cmd2] [&& cmd3] [cmd4] [|| cmd5]` \
**Output:**
```
terminal:
	VSCODE_GIT_ASKPASS_NODE=/home/we/.vscode-server/bin/b1c0a14de1414fcdaa400695b4db1c0799bc3124/node
	VSCODE_GIT_ASKPASS_EXTRA_ARGS=
	VSCODE_GIT_IPC_HANDLE=/mnt/wslg/runtime-dir/vscode-git-9531c9848e.sock
	WSLENV=VSCODE_WSL_EXT_LOCATION/up
	VSCODE_GIT_ASKPASS_MAIN=/home/we/.vscode-server/bin/b1c0a14de1414fcdaa400695b4db1c0799bc3124/extensions/git/dist/askpass-main.js
	VSCODE_IPC_HOOK_CLI=/mnt/wslg/runtime-dir/vscode-ipc-af83fa7b-59bf-4a8f-b326-b2060fd204ec.sock
	cat: not_exist: No such file or directory
	working as inteded
```
```
output.txt:
	working as intended
```