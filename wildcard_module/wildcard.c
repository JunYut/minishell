# include "wildcard.h"

char	**wildcard(char *str, t_env *env)
{
	(void)str;
	t_wildcard	*wc;
	char		**arr;

	wc = init_wc(fetch_val("PWD", env));
	wc->token = tokenize(str);
	arr = lst_to_arr(wc->files);
	return (arr);
}

char	**lst_to_arr(t_list *lst)
{
	char	**arr;
	t_list	*tmp;
	int		i;

	arr = gb_malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	tmp = lst;
	i = -1;
	while (tmp)
	{
		arr[++i] = tmp->content;
		tmp = tmp->next;
	}
	arr[++i] = NULL;
	return (arr);
}

t_wildcard	*init_wc(char *cwd)
{
	t_wildcard		*wc;
	DIR				*dirp;
	struct dirent	*dp;

	wc = gb_malloc(sizeof(t_wildcard));
	wc->files = NULL;
	wc->dot_files = NULL;
	dirp = opendir(cwd);
	dp = readdir(dirp);
	while (dp != NULL)
	{
		if (dp->d_name[0] == '.')
			ft_lstadd_back(&wc->dot_files, gb_lstnew(gb_strdup(dp->d_name)));
		else
			ft_lstadd_back(&wc->files, gb_lstnew(gb_strdup(dp->d_name)));
		dp = readdir(dirp);
	}
	closedir(dirp);
	sort_lex(wc->files);
	sort_lex(wc->dot_files);
	return (wc);
}
