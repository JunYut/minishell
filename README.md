# Work Flow
1. List all requirements
2. Study `bash` behaviours
3. Study all allowed functions (I suggest creating a `sandbox` branch to play around)
4. The rest I need to study about `bash` first to figure out lol, feel free to add on :)

# Git Rules
0. Recommend to install 'Git Graph' extension on `vscode` for better git visualization.
1. Commands
   	- `git restore .`: unstage all changes
   	- `git add .`: stage all changes of the current directory and its subdirectory
   	- `git add -a`: stage all changes of the entire repo
   	- `git add -u`: stage all tracked files
   	- `git commit -m`: Use this to write single line comments
	- `git commit`: Use this to write multiline comments
 	- `git commit --amend`: Use this to edit previous commit message or append latest changes
 	- `git commit -am`: Use this to add stage and commit
   	- `git reset --hard HEAD~1`: Go back to previous commit 
  	- `git reset --soft HEAD~1`: Go back to previous commit while keeping the changes
3. Template messages for different scenarios:
  - New feature prototype:	"PROTOTYPE: implemented prototype of <function_name>"
  - Featurt tweaking: 		"<file_path/function_name>: now does <functionality>"
  - Found issue/bug: 		"ISSUE: <issue_example>"
  - Fixed issue/bug: 		"@<commit_hash>: fixed <issue_example>. Solved by <changes>"
  - Code refactor: 		"REFACTOR: <file_path/function_name>: <changes>"
  - TODO: 			"TODO: implement <feature_name>"
