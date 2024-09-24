/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:53:12 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/24 15:13:36 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char **path, t_env *e)
{
	char	*target;
	char	cwd[1024];

	if (count_args(path, "cd") > 1)
		return (1);
	target = set_target(path, e);
	if (!target)
	{
		print_err("cd", "OLDPWD not set");
		(init_vars(NULL, NULL)->exit_status = 1, ft_free((void **)&target));
		return (1);
	}
	if (!fetch_val("OLDPWD", e))
		add_ent(e, "OLDPWD", fetch_val("PWD", e));
	if (chdir(target) == -1)
	{
		perror("minishell: cd");
		(init_vars(NULL, NULL)->exit_status = 1, ft_free((void **)&target));
		return (1);
	}
	else
		set_val(e, "OLDPWD", fetch_val("PWD", e));
	(getcwd(cwd, 1024), set_val(e, "PWD", cwd));
	ft_free((void **)&target);
	return (0);
}

char	*set_target(char **path, t_env *e)
{
	char	*target;

	target = *path;
	if (!*path || **path == '\0' || **path == '~')
		target = fetch_val("HOME", e);
	else if (ft_strcmp(*path, "-") == 0)
		target = fetch_val("OLDPWD", e);
	if (target)
		target = ft_strdup(target);
	if (*path && ft_strcmp(*path, "-") == 0 && !target)
		return (NULL);
	else if (*path && ft_strcmp(*path, "-") == 0 && target)
		printf("%s\n", target);
	if (*path && **path == '~' && *(*path + 1) != '\0')
		target = gnl_strjoin(target, *path + 1);
	return (target);
}

// if key is not found, return NULL
char	*fetch_val(char *key, t_env *e)
{
	t_var	*ent;

	ent = find_ent(key, e->var);
	if (!ent)
		return (NULL);
	return (ent->value);
}

int	count_args(char **path, char *func)
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
		init_vars(NULL, NULL)->exit_status = 1;
	}
	return (i);
}
