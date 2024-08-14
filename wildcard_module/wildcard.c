# include "wildcard.h"

char	**wildcard(char *str)
{
	(void)str;

	DIR *dirp;
	struct dirent *dp;

	dirp = opendir(".");
	dp = readdir(dirp);
	while (dp != NULL)
	{
		printf("%s", dp->d_name);
		dp = readdir(dirp);
		if (dp != NULL)
			printf(" ");
	}
	printf("\n");
	closedir(dirp);
	return (NULL);
}
