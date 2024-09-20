/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:15:23 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/20 11:20:22 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(char **ent, t_env *e)
{
	char	**split;
	int		status;
	int		i;

	if (ent == NULL || ent[0] == NULL || ent[0][0] == '\0')
	{
		builtin_env(e, EXPORT);
		return (ERRNO_SUCCESS);
	}
	status = 0;
	i = -1;
	while (ent[++i])
	{
		split = split_ent(ent[i]);
		if (!valid_key(split[0]))
		{
			status = 1;
			continue ;
		}
		export(split[0], split[1], e);
		ft_free_s_arr(split);
	}
	sort_export(e->exp);
	ft_free_s_arr(e->envp);
	e->envp = env_to_arr(e->var);
	return (status);
}

int	export(char *key, char *val, t_env *e)
{
	t_var	*ent;

	ent = find_ent(key, e->var);
	if (ent)
		set_val(e, key, val);
	else
		add_ent(e, key, val);
	return (0);
}

void	set_val(t_env *e, char *key, char *val)
{
	t_var	*ent;

	ent = find_ent(key, e->var);
	if (ent)
	{
		ft_free((void **)&ent->value);
		ent->value = ft_strdup(val);
	}
	ent = find_ent(key, e->exp);
	if (ent)
	{
		ft_free((void **)&ent->value);
		ent->value = ft_strdup(val);
	}
	ft_free_s_arr(e->envp);
	e->envp = env_to_arr(e->var);
}

void	sort_export(t_var *exp)
{
	t_var	*curr;
	char	*tmp;

	curr = exp;
	while (curr && curr->next)
	{
		if (curr->key && curr->next->key
			&& ft_strcmp(curr->key, curr->next->key) > 0)
		{
			tmp = curr->key;
			curr->key = curr->next->key;
			curr->next->key = tmp;
			tmp = curr->value;
			curr->value = curr->next->value;
			curr->next->value = tmp;
			curr = exp;
		}
		else
			curr = curr->next;
	}
}

int	valid_key(char *key)
{
	int	i;

	if (!key || ft_strchr("1234567890", key[0]) != NULL)
	{
		print_builtin_err("export", key, "not a valid identifier");
		init_vars(NULL, NULL)->exit_status = 1;
		return (0);
	}
	i = -1;
	while (key[++i])
	{
		if (ft_strchr("!@#$%^&()_+{}|:\"<>?`~-=[]\\;',./", key[i]) != NULL)
		{
			print_builtin_err("export", key, "not a valid identifier");
			init_vars(NULL, NULL)->exit_status = 1;
			return (0);
		}
	}
	return (1);
}
