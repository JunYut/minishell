/*
	char *getcwd(char *, size_t)

	char *: pointer to a buffer where the current working directory will be stored
	char *: pointer to a buffer where the current working directory will be stored
	size_t: size of the buffer
*/

/*
	int chdir(const char *)

	int: 0 on success, -1 on error
	const char *: path to the directory to change to

	Changes the current working directory to the specified directory

	This is a system call that changes the current working directory of the
	calling process to the directory specified in the path. The change of
	directory is global to the process, meaning that all threads in the process
	will see the change of directory. The child processes of the calling process
	will inherit the new working directory.

	Errors:
		- EACCES: search permission is denied for any component of the path
		- ENOENT: the file does not exist
		- ENOTDIR: a component of the path is not a directory
		- EFAULT: path points outside the process's allocated address space
		- EIO: an I/O error occurred
		- ELOOP: too many symbolic links were encountered in translating the pathname
		- ENAMETOOLONG: the path is too long
		- ENOMEM: insufficient kernel memory was available
		- ENOTDIR: a component of the path prefix is not a directory
		- EROFS: the file is on a read-only filesystem
*/

/*
	int isatty(int __fd)

	int: 1 if the file descriptor is associated with a terminal, 0 otherwise
	int __fd: file descriptor

	Checks if the file descriptor is associated with a terminal

	Note:
	- a terminal in a traditional sense is a device that allows the user to
	interact with the computer. This includes the keyboard and the screen. In
	modern systems, the terminal is a software program that provides a command
	line interface for the user to interact with the computer.

	- TTY is an abbreviation for teletypewriter, which is a device that allows
	the user to send and receive messages over a network. In the context of
	Unix-like systems, TTY refers to the terminal device file that provides the
	command line interface for the user to interact with the computer. These files
	are located in the /dev directory and are named tty followed by a number.
*/

/*
	char *ttyname(int __fd)

	char *: pointer to the name of the terminal device file
	int __fd: file descriptor

	Returns the name of the terminal device file associated with the file descriptor
	This name is a path to the terminal device file in the /dev directory
*/

/*
	char *getenv(const char *__name)	*from <stdlib.h>

	char *: pointer to the value of the environment variable
	const char *__name: name of the environment variable

	Returns the value of the environment variable with the specified name
	If the environment variable does not exist, NULL is returned

	Note:
	- Environment variables are global variables that are used to pass information
	from the shell to the programs that it starts. They are stored in the environment
	block of the process and are accessible to all the programs that are started by
	the shell. The environment block is an array of null-terminated strings, where
	each string is in the form name=value.
	- Some common environment variables include:
	1. PATH: a colon-separated list of directories where the shell looks for
		commands to execute
	2. HOME: the path to the user's home directory
	3. USER: the name of the user who is currently logged in
	4. SHELL: the path to the user's default shell
	5. PWD: the current working directory of the shell
	6. TERM: the type of terminal that the shell is running in
	7. LANG: the language and locale settings of the shell
	8. DISPLAY: the display server that the shell is connected to
	9. EDITOR: the default text editor that the shell uses
	10. HOSTNAME: the name of the host computer
	11. LOGNAME: the name of the user who is currently logged in
	12. OLDPWD: the previous working directory of the shell
	13. PS1: the prompt string that is displayed by the shell
*/

/*
	int ttyslot(void)

	int: the number of the terminal device file

	The ttyslot() function doesn't take any arguments and returns an integer. If
	the user's terminal is found in the utmp file, ttyslot() returns the index
	of the entry. If the user's terminal is not found or if an error occurs,
	ttyslot() returns 0.

	Note:
	- The utmp file is a system file that contains information about the users
	who are currently logged in to the system. It is located at /var/run/utmp
	and is used by various system utilities to display information about the
	users who are logged in.
*/

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

int main(void)
{
	// getcwd() & chdir()
	char cwd[1024];

	printf("Current working directory: %s\n", getcwd(cwd, sizeof(cwd)));
	if (chdir("..") == -1)
		perror("..");
	printf("Current working directory: %s\n", getcwd(cwd, sizeof(cwd)));
	if (chdir("~") == -1)
		perror("~");
	printf("Current working directory: %s\n", getcwd(cwd, sizeof(cwd)));
	if (chdir("~we") == -1)
		perror("~we");
	printf("Current working directory: %s\n", getcwd(cwd, sizeof(cwd)));
	if (chdir(".") == -1)
		perror(".");
	printf("Current working directory: %s\n", getcwd(cwd, sizeof(cwd)));
	if (chdir("-") == -1)
		perror("-");
	printf("Current working directory: %s\n", getcwd(cwd, sizeof(cwd)));
	if (chdir("") == -1)
		perror("");
	printf("Current working directory: %s\n", getcwd(cwd, sizeof(cwd)));
	if (chdir("") == -1) // must be a non-NULL string
		printf("must be a non-NULL string\n");
	printf("Current working directory: %s\n", getcwd(cwd, sizeof(cwd)));
	if (chdir("env_module") == -1) // must be a non-NULL string
		perror("env_module");
	printf("Current working directory: %s\n", getcwd(cwd, sizeof(cwd)));

	printf("\n");

	// // isatty()
	// if (isatty(STDIN_FILENO))
	// 	printf("stdin is a terminal\n");
	// if (isatty(STDOUT_FILENO))
	// 	printf("stdout is a terminal\n");
	// if (isatty(STDERR_FILENO))
	// 	printf("stderr is a terminal\n");
	// printf("\n");

	// // ttyname()
	// printf("stdin: %s\n", ttyname(STDIN_FILENO));
	// printf("stdout: %s\n", ttyname(STDOUT_FILENO));
	// printf("stderr: %s\n", ttyname(STDERR_FILENO));
	// // will get same file cuz connected to the same terminal device file
	// printf("\n");

	// // getenv()
	// printf("PATH: %s\n", getenv("PATH"));
	// printf("HOME: %s\n", getenv("HOME"));
	// printf("USER: %s\n", getenv("USER"));
	// printf("SHELL: %s\n", getenv("SHELL"));
	// printf("PWD: %s\n", getenv("PWD"));
	// printf("\n");

	// // ttyslot()
	// printf("Terminal number: %d\n", ttyslot());
}
