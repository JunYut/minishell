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
	isatty()
*/

/*
	ttyname()
*/

/*
	getenv()
*/

# include <unistd.h>
# include <stdio.h>

int main(void)
{
	char cwd[1024];

	// getcwd() & chdir()
	printf("Current working directory: %s\n", getcwd(cwd, sizeof(cwd)));
	if (chdir("../") == -1)
		perror("chdir");
	printf("Current working directory: %s\n", getcwd(cwd, sizeof(cwd)));

	// isatty()
	if (isatty(STDIN_FILENO))
		printf("stdin is a terminal\n");
	if (isatty(STDOUT_FILENO))
		printf("stdout is a terminal\n");
	if (isatty(STDERR_FILENO))
		printf("stderr is a terminal\n");
}
