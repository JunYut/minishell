/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:15:23 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/23 09:38:20 by tjun-yu          ###   ########.fr       */
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
			(ft_free_s_arr(split), status = 1);
			continue ;
		}
		export(split[0], split[1], e);
		ft_free_s_arr(split);
	}
	sort_export(e->exp);
	update_envp(e);
	return (status);
}

// if key is found but val is NULL do nothing
// if both list doesn't have the key, add to both list
// if var list has the key, update the value of both list
// if only exp list has the key, update the value, add to var list
int	export(char *key, char *val, t_env *e)
{
	t_var	*ent_var;
	t_var	*ent_exp;

	ent_var = find_ent(key, e->var);
	ent_exp = find_ent(key, e->exp);
	if (ent_exp && !val)
		return (0);
	if (!ent_var && !ent_exp)
		add_ent(e, key, val);
	else if (ent_exp && !ent_var)
	{
		set_val(e, key, val);
		add_ent(e, key, val);
	}
	else if (ent_var)
		set_val(e, key, val);
	return (0);
}

void	set_val(t_env *e, char *key, char *val)
{
	t_var	*ent;

	ent = find_ent(key, e->var);
	if (ent)
	{
		ft_free((void **)&ent->value);
		if (!val)
			ent->value = NULL;
		else
			ent->value = ft_strdup(val);
	}
	ent = find_ent(key, e->exp);
	if (ent)
	{
		ft_free((void **)&ent->value);
		if (!val)
			ent->value = NULL;
		else
			ent->value = ft_strdup(val);
	}
	update_envp(e);
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
