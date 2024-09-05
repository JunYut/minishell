/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:10:42 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/05 16:51:23 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "expand.h"
#include "utils.h"

char	**wildcard(char *regex, t_env *env_var)
{
	t_wildcard	*wc;
	t_list		*match_lst;

	wc = gbc_malloc(sizeof(t_wildcard));
	wc->dirent = init_dirent(fetch_val("PWD", env_var));
	wc->token = tokenize_wc(regex);
	wc->pattern = ft_split(regex, '*');
	match_lst = ent_match(wc, regex);
	if (match_lst == NULL)
		ft_lstadd_back(&match_lst, gbc_lstnew(gbc_strdup(regex)));
	ft_free_s_arr(wc->pattern);
	return (lst_to_arr(match_lst));
}

char	**lst_to_arr(t_list *lst)
{
	char	**arr;
	t_list	*tmp;
	int		i;

	arr = gbc_malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
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
	t_dirent		*ent;
	DIR				*dirp;
	struct dirent	*dp;

	ent = gbc_malloc(sizeof(t_dirent));
	ent->files = NULL;
	ent->dot_files = NULL;
	dirp = opendir(cwd);
	dp = readdir(dirp);
	while (dp != NULL)
	{
		if (dp->d_name[0] == '.')
			ft_lstadd_back(&ent->dot_files, gbc_lstnew(gbc_strdup(dp->d_name)));
		else
			ft_lstadd_back(&ent->files, gbc_lstnew(gbc_strdup(dp->d_name)));
		dp = readdir(dirp);
	}
	closedir(dirp);
	sort_lex(ent->files);
	sort_lex(ent->dot_files);
	return (ent);
}
