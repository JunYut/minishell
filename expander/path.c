/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:52:25 by we                #+#    #+#             */
/*   Updated: 2024/09/06 15:53:25 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char	*parse_path(char *envp[], char *cmd)
{
	char	**path_list;
	char	*path;
	int		i;

	i = -1;
	while (envp[++i] && ft_strncmp(envp[i], "PATH=", 5))
		;
	path_list = ft_split(envp[i], ':');
	prepend_cmd(path_list, cmd);
	trim_path(path_list[0], "PATH=");
	path = NULL;
	i = -1;
	while (path_list[++i] && !path)
		if (access(path_list[i], X_OK) == 0)
			path = ft_strdup(path_list[i]);
	ft_free_s_arr(path_list);
	return (path);
}

void	trim_path(char *cmd, char *path)
{
	size_t	path_len;

	path_len = ft_strlen(path);
	ft_memmove(cmd, cmd + path_len, ft_strlen(cmd) - path_len);
	cmd[ft_strlen(cmd) - path_len] = '\0';
}

void	prepend_cmd(char **path_list, char *cmd)
{
	int	i;

	i = -1;
	while (path_list[++i])
	{
		path_list[i] = gnl_strjoin(path_list[i], "/");
		path_list[i] = gnl_strjoin(path_list[i], cmd);
	}
}

void	append_str(char **str1, char *str2)
{
	int		i;
	int		j;
	char	*new;

	i = -1;
	j = -1;
	new = gbc_malloc(ft_strlen(*str1) + ft_strlen(str2) + 1);
	while ((*str1)[++i])
		new[i] = (*str1)[i];
	while (str2[++j])
		new[i + j] = str2[j];
	new[i + j] = '\0';
	*str1 = new;
}
