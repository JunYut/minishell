/*
	pid_t fork(void)

	pid_t: Return -1 for errors, 0 to the new process, and the process ID of the
		   new process to the old process.

	The fork() function is a system call in Unix-like operating systems that
	creates a new process. The new process, called the child, is an exact copy of
	the calling process, called the parent, except for a few values that are
	changed, such as the process ID and parent process ID.

	The child process gets a copy of the parent's memory space. This includes the
	program code and the values of all variables at the time fork() was called.
	However, the child process does not share memory with the parent process. Any
	changes that the child process makes to its memory space do not affect the
	parent's memory space, and vice versa.

	The child process also gets copies of the parent's file descriptors. These
	file descriptors point to the same open files as the parent's file descriptors,
	so both the parent and child can read from and write to the same files.

	The fork() function returns twice: once in the parent process, where it
	returns the process ID of the child process, and once in the child process,
	where it returns 0. This is how the parent and child can distinguish between
	each other: the parent checks if the return value of fork() is greater than 0,
	and the child checks if it is 0.

	Note:
	1. the child process continues executing from the point where fork() was
	called. This means that the parent and child processes will both execute the
	same code after the fork() call.

	2. After a child process terminates, some of its data structures remain in the
	system, like the process ID, the termination status of the child, and other
	information. This is known as a "zombie" process. It doesn't consume any
	resources, but it does hold a place in the process table. To clean up these
	"zombie" processes, the parent process should call wait(), waitpid(), wait3(),
	or wait4(). These functions allow the parent process to	collect the termination
	status of its child and tell the system it can free the resources it was
	holding for the child process.
*/

/*
	pid_t wait(int *__stat_loc)

	pid_t: Return -1 for errors, the process ID of the terminated child process
		   for success.
	int *__stat_loc: A pointer to an integer where the termination status of the
					child process will be stored.

	The wait() function is a system call in Unix-like operating systems that
	suspends the execution of the calling process until one of its child processes
	terminates. If the calling process has no child processes, the wait() function
	returns immediately with an error.
*/

/*
	__pid_t waitpid(pid_t __pid, int *__stat_loc, int __options)

	__pid_t: Return -1 for errors, the process ID of the terminated child process
			 for success.
	pid_t __pid: The process ID of the child process to wait for. If __pid is
				 -1, the waitpid() function waits for any child process.
	int *__stat_loc: A pointer to an integer where the termination status of the
					child process will be stored.
*/

/*
	pid_t wait3(int *__stat_loc, int __options, struct rusage *__usage)

	pid_t: Return -1 for errors, the process ID of the terminated child process
		   for success.
	int *__stat_loc: A pointer to an integer where the termination status of the
					child process will be stored.
	int __options: A set of options that control the behavior of the wait3()
				   function. This argument is not used in modern systems and should
				   be set to 0.
*/

/*
	pid_t wait4(pid_t __pid, int *__stat_loc, int __options, struct rusage *__usage)

	pid_t: Return -1 for errors, the process ID of the terminated child process
		   for success.
	pid_t __pid: The process ID of the child process to wait for. If __pid is -1,
				 the wait4() function waits for any child process.
	int *__stat_loc: A pointer to an integer where the termination status of the
					child process will be stored.
	int __options: A set of options that control the behavior of the wait4()
				   function. This argument is not used in modern systems and should
				   be set to 0.
*/

# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>

int main(void)
{
	pid_t pid;

	// wait(): use when you don't care which child process terminates
	pid = fork();
	if (pid == 0)
	{
		// since there is no child process, the return value of getpid() is 0
		printf("child: %d, %d\n", getpid(), pid);
		return 0;
	}
	else
	{
		wait(NULL);
		printf("parent: %d, %d\n", getpid(), pid);
		printf("\n");
	}

	// waitpid(): use when you want to wait for a specific child process to
	//	terminate
	pid = fork();
	if (pid == 0)
	{
		printf("child: %d, %d\n", getpid(), pid);
		return 0;
	}
	else
	{
		waitpid(pid, NULL, 0);
		printf("parent: %d, %d\n", getpid(), pid);
		printf("\n");
	}

	// wait3(): same as wait(), but with an additional argument for resource usage
	pid = fork();
	if (pid == 0)
	{
		printf("child: %d, %d\n", getpid(), pid);
		return 0;
	}
	else
	{
		wait3(NULL, 0, NULL);
		printf("parent: %d, %d\n", getpid(), pid);
		printf("\n");
	}

	// wait4(): same as waitpid(), but with an additional argument for resource
	//			usage
	pid = fork();
	if (pid == 0)
	{
		printf("child: %d, %d\n", getpid(), pid);
		return 0;
	}
	else
	{
		wait4(pid, NULL, 0, NULL);
		printf("parent: %d, %d\n", getpid(), pid);
		printf("\n");
	}
}
