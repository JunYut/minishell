/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:16:18 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/06 09:33:08 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*dup_env(char **envp)
{
	t_env	*e;
	char	**split;
	int		i;

	e = gb_malloc(sizeof(t_env));
	e->exp = gb_malloc(sizeof(t_var));
	e->var = gb_malloc(sizeof(t_var));
	e->exp->next = NULL;
	e->var->next = NULL;
	i = -1;
	while (envp[++i])
	{
		split = split_var(envp[i]);
		add_var(e, split[0], split[1]);
	}
	unset("OLDPWD", e);
	add_var(e, "?", "1");
	set_val(e, "SHLVL", "1");
	return (e);
}

void	env(t_env *e, char lst)
{
	t_var	*curr;

	if (lst == VAR)
		curr = e->var;
	else
		curr = e->exp;
	while (curr->next)
	{
		if (lst == EXPORT)
			printf("declare -x ");
		printf("%s=", curr->key);
		if (lst == EXPORT && curr->value)
			printf("\"%s\"\n", curr->value);
		else if (lst == VAR && curr->value)
			printf("%s\n", curr->value);
		// else
		// 	;
		curr = curr->next;
	}
}

void	unset(char *key, t_env *v)
{
	t_var	*curr;

	if (key == NULL)
		return ;
	curr = v->var;
	while (curr->next)
	{
		if (ft_strcmp(curr->next->key, key) == 0)
		{
			curr->next = curr->next->next;
			return ;
		}
		curr = curr->next;
	}
	curr = v->exp;
	while (curr->next)
	{
		if (ft_strcmp(curr->next->key, key) == 0)
		{
			curr->next = curr->next->next;
			return ;
		}
		curr = curr->next;
	}
}

// a=1 : export: a="1"; var: a=1
// a= : export: a=""; var: a=
// a : export: a; var: [nothing]
void	add_var(t_env *e, char *key, char *val)
{
	static int	id;
	t_var		*curr;

	curr = e->exp;
	while (curr->next)
		curr = curr->next;
	curr->id = id++;
	curr->key = key;
	curr->value = val;
	curr->next = gb_malloc(sizeof(t_var));
	curr->next->next = NULL;
	if (val == NULL)
		return ;
	curr = e->var;
	while (curr->next)
		curr = curr->next;
	curr->id = id;
	curr->key = key;
	curr->value = val;
	curr->next = gb_malloc(sizeof(t_var));
	curr->next->next = NULL;
}

char **split_var(char *str)
{
	char	**split;

	if (str == NULL)
		return (NULL);
	split = gb_malloc(sizeof(char *) * 2);
	split[0] = ft_strndup(str, find_pos(str, '='));
	if (split[0] == NULL)
	{
		split[0] = ft_strndup(str, find_pos(str, '='));
		split[1] = NULL;
		return (split);
	}
	split[1] = ft_strndup(str + find_pos(str, '=') + 1, find_pos(str, '\0'));
	return (split);
}

int	find_pos(char *str, char delim)
{
	int i;

	i = -1;
	while (str[++i] && str[i] != delim)
		;
	if (str[i] != delim)
		return (-1);
	return (i);
}

char	*ft_strndup(char *str, int pos)
{
	char	*dup;

	dup = gb_malloc(pos + 1);
	ft_strncpy(dup, str, pos);
	return (dup);
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

void ft_strncpy(char *dst, char *src, int len)
{
	int i;

	i = -1;
	while (++i < len && src[i])
		dst[i] = src[i];
	dst[i] = '\0';
}

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
