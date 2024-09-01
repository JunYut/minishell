/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:15:23 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/01 14:27:04 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(char **ent, t_env *e)
{
	char	**split;
	char	*value;
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
		if (valid_key(split[0], e) == 1)
		{
			status = 1;
			continue ;
		}
		value = fetch_val(split[0], e);
		if (value)
			set_val(e, split[0], split[1]);
		else
			add_ent(e, split[0], split[1]);
	}
	sort_export(e->exp);
	e->envp = env_to_arr(e->var);
	return (status);
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

void	set_val(t_env *e, char *key, char *val)
{
	t_var	*curr;

	curr = e->exp;
	while (curr->next)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			curr->value = val;
			break;
		}
		curr = curr->next;
	}
	curr = e->var;
	while (curr->next)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			curr->value = val;
			return ;
		}
		curr = curr->next;
	}
}

// a=1 : export: a="1"; var: a=1
// a= : export: a=""; var: a=
// a : export: a; var: [nothing]
char **split_ent(char *str)
{
	char	**split;

	if (str == NULL)
		return (NULL);
	split = gb_malloc(sizeof(char *) * 2);
	split[0] = ft_strndup(str, find_pos(str, '='));
	if (split[0] == NULL)
	{
		split[0] = ft_strndup(str, find_pos(str, '\0'));
		split[1] = NULL;
		return (split);
	}
	split[1] = ft_strndup(str + find_pos(str, '=') + 1, find_pos(str, '\0'));
	return (split);
}

void sort_export(t_var *exp)
{
	t_var	*curr;
	char	*tmp;

	curr = exp;
	while (curr->next && curr->next->next)
	{
		if (ft_strcmp(curr->key, curr->next->key) > 0)
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

int	valid_key(char *key, t_env *e)
{
	int	i;


	if (!key || ft_strchr("1234567890", key[0]) != NULL)
	{
		printf("Did it reach here?\n");
		printf("minishell: export: `%s`: not a valid identifier\n", key);
		set_val(e, "?", "1");
		return (1);
	}
	i = -1;
	while (key[++i])
	{
		if (ft_strchr("!@#$%^&()_+{}|:\"<>?`~-=[]\\;',./", key[i]) != NULL)
		{
			printf("minishell: export: `%s`: not a valid identifier\n", key);
			set_val(e, "?", "1");
			return (1);
		}
	}
	return (0);
}
