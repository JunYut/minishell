# include "wildcard.h"

char	**wildcard(char *str, t_env *env)
{
	(void)str;
	t_wildcard	*wc;
	char		**arr;

	wc = init_wc(fetch_val("PWD", env));
	arr = NULL;
	return (arr);
}

t_wildcard	*init_wc(char *cwd)
{
	t_wildcard		*wc;
	DIR				*dirp;
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
			ft_lstadd_back(&wc->dot_files, gb_add(ft_lstnew(gb_add(ft_strdup(dp->d_name)))));
		else
			ft_lstadd_back(&wc->files, gb_add(ft_lstnew(gb_add(ft_strdup(dp->d_name)))));
		dp = readdir(dirp);
	}
	closedir(dirp);
	return (wc);
}
