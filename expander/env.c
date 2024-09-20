/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:16:18 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/20 10:47:25 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "minishell.h"
#include "utils.h"

t_env	*dup_env(char *envp[], char *name)
{
	t_env	*e;
	char	**split;
	int		i;

	e = malloc(sizeof(t_env));
	e->envp = NULL;
	e->exp = NULL;
	e->var = NULL;
	e->last_exp_id = 0;
	e->last_var_id = 0;
	i = -1;
	while (envp[++i])
	{
		split = split_ent(envp[i]);
		add_ent(e, split[0], split[1]);
		ft_free_s_arr(split);
	}
	builtin_unset((char *[]){"OLDPWD", NULL}, e);
	set_val(e, "SHELL", name);
	sort_export(e->exp);
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
	while (curr)
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
	new_ent(&e->exp, key, val, e->last_exp_id);
	if (val == NULL)
		return ;
	e->last_var_id += 1;
	new_ent(&e->var, key, val, e->last_var_id);
}

// a=1 : export: a="1"; var: a=1
// a= : export: a=""; var: a=
// a : export: a; var: [nothing]
char	**split_ent(char *str)
{
	char	**split;

	if (str == NULL)
		return (NULL);
	split = malloc(sizeof(char *) * 3);
	split[0] = ft_strndup(str, find_pos(str, '='));
	if (split[0] == NULL)
	{
		split[0] = ft_strndup(str, find_pos(str, '\0'));
		split[1] = NULL;
		return (split);
	}
	split[1] = ft_strndup(str + find_pos(str, '=') + 1, find_pos(str, '\0'));
	split[2] = NULL;
	return (split);
}

char	**env_to_arr(t_var *var)
{
	char	**arr;
	t_var	*curr;
	int		size;

	size = 0;
	curr = var;
	while (curr)
	{
		++size;
		curr = curr->next;
	}
	arr = malloc(sizeof(char *) * (size + 1));
	arr[size] = NULL;
	curr = var;
	size = -1;
	while (curr)
	{
		arr[++size] = ft_strjoin(curr->key, "=");
		arr[size] = ft_strjoin(arr[size], curr->value);
		curr = curr->next;
	}
	return (arr);
}
