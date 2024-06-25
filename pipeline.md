# minishell
while (1)
{
	Read the input from the user
	Check if the input is valid
	If the input is valid, call the function to perform the operation
	If the input is invalid, print an error message
}

# Input Analyzing
## Display current working directory
pwd

[command]

## Change directory
`cd /path/to/directory`

[command] [argument]

## Copy file
`cp source_file destination_file`

[command] [argument_1] [argument_2]

## List files and directories
`ls -l`

[command] [options]

## Remove a directory and its contents
`rm -r directory_to_remove`

[command] [options] [argument]

## Find files and directories
`find /path/to/search -name "search_pattern"`

[command] [argument_1] [options] [argument_2]

## Chain commands
`command1 && command2`

[command_1] [operator] [command_2]

## Redirect output to a file
`echo "Some text" > file.txt`

[command] [argument_1] [operator] [argument_2]

## List out all files & directories and print hello
`echo -n what the fuck && ls -a ../`

[command] [options] [arguments] [operator] [command] [options] [arguments]

## Summary
1. First command string should be a `command`
2. After a `command`, the next command string should be either `options`, `arguments` or `operator`
3. After `options`, the next command string should be either `arguments` or `operator`
4. After `arguments`, the next command string should be either `operator` or `options`
5. After an `operator`, the next command string should be a `command`
6. Syntax Tree
```
	|- [command]
	|	|- [command] [arguments]
	|	|	|- [command] [arguments] [options]
	|	|	|- [command] [arguments] [operator]
	|	|
	|	|- [command] [options]
	|	|	|- [command] [options] [arguments]
	|	|	|- [command] [options] [operator]
	|	|
	|	|- [command] [operator]
	|		|- [command] [operator] [command]
	|
	|- [heredoc]
		|- [heredoc] [command]
		|- [heredoc] [operator]
```
# Operators
`<`: Redirects standard input (stdin) from a file.\
`>`: Redirects standard output (stdout) to a file, overwriting the file.\
`<<`: Redirects heredoc to a command.\
`>>`: Redirects standard output (stdout) to a file, appending to the file.\
`|`: Pipe. Sends the output of one command to another command as input.\
`&&`: Logical AND. Executes the second command only if the first command succeeds.\
`||`: Logical OR. Executes the second command only if the first command fails.\
`()`: Create a subshell to execute commands in the parentheses. Any changes to variables in the subshell should not affect the parent shell.\
`''`: Single quotes. Encloses a string, preventing variable expansion and command substitution.\
`""` : Double quotes. Encloses a string, allowing variable expansion and command substitution.