# include "wildcard.h"

char	**wildcard(char *regex, t_env *env)
{
	t_wildcard	*wc;
	t_list		*match_lst;

	wc = gb_malloc(sizeof(t_wildcard));
	wc->dirent = init_dirent(fetch_val("PWD", env));
	wc->token = tokenize(regex);
	wc->pattern = ft_split(regex, '*');
	match_lst = ent_match(wc, regex);
	if (match_lst == NULL)
		ft_lstadd_back(&match_lst, gb_lstnew(gb_strdup(regex)));
	ft_free_s_arr(wc->pattern);
	return (lst_to_arr(match_lst));
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

t_dirent	*init_dirent(char *cwd)
{
	t_dirent		*dirent;
	DIR				*dirp;
	struct dirent	*dp;

	dirent = gb_malloc(sizeof(t_dirent));
	dirent->files = NULL;
	dirent->dot_files = NULL;
	dirp = opendir(cwd);
	dp = readdir(dirp);
	while (dp != NULL)
	{
		if (dp->d_name[0] == '.')
			ft_lstadd_back(&dirent->dot_files, gb_lstnew(gb_strdup(dp->d_name)));
		else
			ft_lstadd_back(&dirent->files, gb_lstnew(gb_strdup(dp->d_name)));
		dp = readdir(dirp);
	}
	closedir(dirp);
	sort_lex(dirent->files);
	sort_lex(dirent->dot_files);
	return (dirent);
}
