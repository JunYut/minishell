/*
	int stat(const char *__restrict__ __file, struct stat *__restrict__ __buf)

	int: The return value of the function is 0 if the function is successful, and
		 -1 if an error occurs.
	const char *__restrict__ __file: The path to the file whose information you
									  want to retrieve.
	struct stat *__restrict__ __buf: A pointer to a stat structure where the
									  information about the file will be stored.
*/

/*
	int lstat(const char *__restrict__ __file, struct stat *__restrict__ __buf)

	int: The return value of the function is 0 if the function is successful, and
		 -1 if an error occurs.
	const char *__restrict__ __file: The path to the file whose information you
									  want to retrieve.
	struct stat *__restrict__ __buf: A pointer to a stat structure where the
									  information about the file will be stored.
*/

/*
	fstat()
*/

# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

int main(void)
{
	struct stat fileInfo;
	int			fd;

	// stat(): retrieves information about the file specified by the path
	stat("stat.c", &fileInfo);

	printf("File size: %ld\n", fileInfo.st_size);
	printf("Number of links: %ld\n", fileInfo.st_nlink);
	printf("File inode: %ld\n", fileInfo.st_ino);
	printf("File permissions: %d\n", fileInfo.st_mode);
	printf("File UID: %d\n", fileInfo.st_uid);
	printf("File GID: %d\n\n", fileInfo.st_gid);

	// lstat(): same as stat(), but can get information about the symbolic link
	lstat("stat.c", &fileInfo);

	printf("File size: %ld\n", fileInfo.st_size);
	printf("Number of links: %ld\n", fileInfo.st_nlink);
	printf("File inode: %ld\n", fileInfo.st_ino);
	printf("File permissions: %d\n", fileInfo.st_mode);
	printf("File UID: %d\n", fileInfo.st_uid);
	printf("File GID: %d\n\n", fileInfo.st_gid);

	// fstat(): use when already opened the file
	fd = open("stat.c", O_RDONLY);
	fstat(fd, &fileInfo);

	printf("File size: %ld\n", fileInfo.st_size);
	printf("Number of links: %ld\n", fileInfo.st_nlink);
	printf("File inode: %ld\n", fileInfo.st_ino);
	printf("File permissions: %d\n", fileInfo.st_mode);
	printf("File UID: %d\n", fileInfo.st_uid);
	printf("File GID: %d\n", fileInfo.st_gid);

	close(fd);

	return 0;
}
