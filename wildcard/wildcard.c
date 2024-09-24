/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:10:42 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/24 10:40:00 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "expand.h"
#include "utils.h"

void	del(void *content)
{
	if (content)
	{
		free(content);
		content = NULL;
	}
}

char	**wildcard(char *regex, t_env *env_var)
{
	t_wildcard	wc;
	t_list		*match_lst;
	char		**result;

	wc.dirent = init_dirent(fetch_val("PWD", env_var));
	wc.token = tokenize_wc(regex);
	wc.pattern = ft_split(regex, '*');
	match_lst = ent_match(&wc, regex);
	if (match_lst == NULL)
		ft_lstadd_back(&match_lst, ft_lstnew(ft_strdup(regex)));
	ft_free_s_arr(wc.pattern);
	result = lst_to_arr(match_lst);
	ft_lstclear(&match_lst, del);
	ft_lstclear(&wc.dirent->dot_files, del);
	ft_lstclear(&wc.dirent->files, del);
	free(wc.dirent);
	free(wc.token);
	return (result);
}

char	**lst_to_arr(t_list *lst)
{
	char	**arr;
	t_list	*tmp;
	int		i;

	arr = ft_calloc((ft_lstsize(lst) + 1), sizeof(char *));
	tmp = lst;
	i = -1;
	while (tmp)
	{
		arr[++i] = ft_strdup(tmp->content);
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

	ent = malloc(sizeof(t_dirent));
	if (!ent)
		return (NULL);
	ent->files = NULL;
	ent->dot_files = NULL;
	dirp = opendir(cwd);
	dp = readdir(dirp);
	while (dp != NULL)
	{
		if (dp->d_name[0] == '.')
			ft_lstadd_back(&ent->dot_files, ft_lstnew(ft_strdup(dp->d_name)));
		else
			ft_lstadd_back(&ent->files, ft_lstnew(ft_strdup(dp->d_name)));
		dp = readdir(dirp);
	}
	closedir(dirp);
	sort_lex(ent->files);
	sort_lex(ent->dot_files);
	return (ent);
}
