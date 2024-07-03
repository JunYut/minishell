# Parsing
`access()`: can take in directory as argument, returns `0` indicating user (or process) has permission to enter the directory and access its contents.
`<< HERE_DOC`: you can do something like `[cmd] HERE_DOC HERE_DOC [arg]`.
`>`: `echo [msg] > file1 > file2`. `msg` will  be written to `file2`, content of `file1` will be erased.
`cat < file1 < file2`: contents of `file2` will be printed.
`cat < file > file`: contents of `file` will be truncated.
`cat < file >> file`: infinite loop until `ctrl+c`.