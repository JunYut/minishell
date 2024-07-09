/*
	A directory entry represents a file in a directory. It contains the name of
	the	file, the type of the file, and the inode number of the file. The dirent.h
	header file contains the definition of the dirent structure, and the functions
	opendir(), readdir(), and closedir() for working with directory entries.
*/

/*
	DIR * opendir(const char *__name)

	DIR *: a pointer to a structure representing a directory stream
	const char *__name: the name of the directory to open

	Opens a directory stream corresponding to the directory name, and returns a
	pointer to the directory stream. The stream can be read using readdir().
*/

/*
	struct dirent *readdir(DIR *__dirp)

	struct dirent *: a pointer to a structure representing a directory entry
	DIR *__dirp: a pointer to a directory stream

	Reads the next directory entry from the directory stream, and returns a pointer
	to a structure containing information about the entry. The structure contains
	the following members:
	- ino_t d_ino: the inode number of the file
	- off_t d_off: the offset of the next directory entry
	- unsigned short d_reclen: the length of the record
	- unsigned char d_type: the type of the file
	- char d_name[]: the name of the file

	The end of the directory stream is indicated by a NULL pointer being returned.
*/

/*
	int closedir(DIR *__dirp)

	int: 0 on success, -1 on failure
	DIR *__dirp: a pointer to a directory stream

	Closes the directory stream, and frees the resources associated with it.
*/

# include <dirent.h>
# include <stdio.h>

int main(void)
{
	DIR *dirp;
	struct dirent *dp;

	dirp = opendir(".");
	dp = readdir(dirp);
	while (dp != NULL)
	{
		printf("%s\n", dp->d_name);
		dp = readdir(dirp);
	}
	closedir(dirp);
}
