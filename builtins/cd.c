/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:53:12 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/02 10:51:19 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char **path, t_env *e)
{
	char	*target;

	if (count_args(path, "cd", e) > 1)
		return (1);
	target = *path;
	if (!*path || **path == '\0' || **path == '~')
		target = fetch_val("HOME", e);
	else if (ft_strcmp(*path, "-") == 0)
		target = fetch_val("OLDPWD", e);
	if (*path && ft_strcmp(*path, "-") == 0 && !target)
	{
		print_err("cd", "OLDPWD not set");
		set_val(e, "?", "1");
		return (1);
	}
	else if (*path && ft_strcmp(*path, "-") == 0 && target)
		printf("%s\n", target);
	if (*path && **path == '~' && *(*path + 1) != '\0')
		target = ft_strjoin(target, *path + 1); // Changed this from joining "/home/" to target
	if (!fetch_val("OLDPWD", e))
		add_ent(e, "OLDPWD", fetch_val("PWD", e));
	if (chdir(target) == -1)
	{
		perror("minishell: cd");
		set_val(e, "?", "1");
		return (1);
	}
	else
		set_val(e, "OLDPWD", fetch_val("PWD", e));
	set_val(e, "PWD", gb_add(getcwd(NULL, 0)));
	return (0);
}

int	count_args(char **path, char *func, t_env *e)
{
	int	i;

	if (!path || !*path)
		return (0);
	i = 0;
	while (path[i])
		i++;
	if (i > 1)
	{
		print_err(func, "too many arguments");
		set_val(e, "?", "1");
	}
	return (i);
}
