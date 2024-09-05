/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:53:12 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/05 11:47:51 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char **path, t_env *e)
{
	char	*target;

	if (count_args(path, "cd", e) > 1)
		return (1);
	target = set_target(path, e);
	if (!target)
	{
		print_err("cd", "OLDPWD not set");
		set_val(e, "?", "1");
		return (1);
	}
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

char	*set_target(char **path, t_env *e)
{
	char	*target;

	target = *path;
	if (!*path || **path == '\0' || **path == '~')
		target = fetch_val("HOME", e);
	else if (ft_strcmp(*path, "-") == 0)
		target = fetch_val("OLDPWD", e);
	if (*path && ft_strcmp(*path, "-") == 0 && !target)
		return (NULL);
	else if (*path && ft_strcmp(*path, "-") == 0 && target)
		printf("%s\n", target);
	if (*path && **path == '~' && *(*path + 1) != '\0')
		target = ft_strjoin(target, *path + 1);
	return (target);
}

// if key is not found, return NULL
char	*fetch_val(char *key, t_env *e)
{
	t_var	*curr;

	curr = e->var;
	while (curr->next)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
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
