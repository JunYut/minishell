/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:16:18 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/17 13:24:11 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "utils.h"

t_env	*dup_env(char *envp[])
{
	t_env	*e;
	char	**split;
	int		i;

	e = malloc(sizeof(t_env));
	e->exp = NULL;
	e->var = NULL;
	e->last_exp_id = 0;
	e->last_var_id = 0;
	i = -1;
	while (envp[++i])
	{
		split = split_ent(envp[i]);
		add_ent(e, split[0], split[1]);
	}
	builtin_unset((char *[]){"OLDPWD", NULL}, e);
	e->envp = env_to_arr(e->var);
	return (e);
}

int	builtin_env(t_env *e, char lst)
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
		printf("%s", curr->key);
		if (lst == EXPORT && curr->value)
			printf("=\"%s\"", curr->value);
		else if (lst == VAR && curr->value)
			printf("=%s", curr->value);
		printf("\n");
		curr = curr->next;
	}
	return (0);
}

// a=1 : export: a="1"; var: a=1
// a= : export: a=""; var: a=
// a : export: a; var: [nothing]
void	add_ent(t_env *e, char *key, char *val)
{
	e->last_exp_id += 1;
	if (e->exp == NULL)
	{
		e->exp = malloc(sizeof(t_var));
		e->exp->key = key;
		e->exp->value = val;
		e->exp->next = NULL;
	}
	new_ent(e->exp, key, val);
	if (val == NULL)
		return ;
	e->last_var_id += 1;
	if (e->var == NULL)
	{
		e->var = malloc(sizeof(t_var));
		e->var->key = key;
		e->var->value = val;
		e->var->next = NULL;
	}
	new_ent(e->var, key, val);
}

// a=1 : export: a="1"; var: a=1
// a= : export: a=""; var: a=
// a : export: a; var: [nothing]
char	**split_ent(char *str)
{
	char	**split;

	if (str == NULL)
		return (NULL);
	split = malloc(sizeof(char *) * 2);
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

char	**env_to_arr(t_var *var)
{
	char	**arr;
	t_var	*curr;
	int		size;

	size = 0;
	curr = var;
	while (curr->next)
	{
		++size;
		curr = curr->next;
	}
	arr = malloc(sizeof(char *) * (size + 1));
	arr[size] = NULL;
	curr = var;
	size = -1;
	while (curr->next)
	{
		if (!curr->key || !curr->value)
			continue ;
		arr[++size] = ft_strjoin(curr->key, "=");
		arr[size] = ft_strjoin(arr[size], curr->value);
		curr = curr->next;
	}
	return (arr);
}
