# include "wildcard.h"

char	**wildcard(char *str, t_env *env)
{
	(void)str;

	DIR *dirp;
	struct dirent *dp;

	dirp = opendir(fetch_val("PWD", env));
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

t_wildcard	*init_wc(char *cwd)
{
	t_wildcard	*wc;
	DIR			*dirp;
	struct dirent	*dp;

	wc = gb_malloc(sizeof(t_wildcard));
	wc->cwd = cwd;
	wc->files = NULL;
	wc->dot_files = NULL;
	dirp = opendir(cwd);
	dp = readdir(dirp);
	while (dp != NULL)
	{
		if (dp->d_name[0] == '.')
			ft_lstadd_back(&wc->dot_files, ft_lstnew(ft_strdup(dp->d_name)));
		else
			ft_lstadd_back(&wc->files, ft_lstnew(ft_strdup(dp->d_name)));
		dp = readdir(dirp);
	}
	return (wc);
}
