/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:16:18 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/01 13:47:41 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

t_env	*dup_env(char *envp[])
{
	t_env	*e;
	char	**split;
	int		i;

	e = gb_malloc(sizeof(t_env));
	e->exp = gb_malloc(sizeof(t_var));
	e->var = gb_malloc(sizeof(t_var));
	e->exp->next = NULL;
	e->var->next = NULL;
	e->last_exp_id = 0;
	e->last_var_id = 0;
	i = -1;
	while (envp[++i])
	{
		split = split_ent(envp[i]);
		add_ent(e, split[0], split[1]);
	}
	builtin_unset((char *[]){"OLDPWD", NULL}, e);
	add_ent(e, "?", "0");
	set_val(e, "SHLVL", "1");
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
		else
			;
		printf("\n");
		curr = curr->next;
	}
	return (0);
}

// void	unset(char **keys, t_env *e)
// {
// 	t_var	*curr;
// 	int		i;

// 	if (keys == NULL || keys[0] == NULL)
// 		return ;
// 	i = -1;
// 	while (keys[++i])
// 	{
// 		curr = e->var;
// 		while (curr->next && curr->id != e->last_var_id)
// 		{
// 			if (ft_strcmp(curr->next->key, keys[i]) == 0)
// 			{
// 				if (curr->next->id == e->last_var_id)
// 				{
// 					e->last_var_id = curr->id;
// 					curr->next->next = NULL;
// 				}
// 				else
// 					curr->next = curr->next->next;
// 				break;
// 			}
// 			curr = curr->next;
// 		}
// 		curr = e->exp;
// 		while (curr->next && curr->id != e->last_exp_id)
// 		{
// 			if (ft_strcmp(curr->next->key, keys[i]) == 0)
// 			{
// 				if (curr->next->id == e->last_exp_id)
// 				{
// 					e->last_exp_id = curr->id;
// 					curr->next->next = NULL;
// 				}
// 				else
// 					curr->next = curr->next->next;
// 				break;
// 			}
// 			curr = curr->next;
// 		}
// 	}
// }

// // a=1 : export: a="1"; var: a=1
// // a= : export: a=""; var: a=
// // a : export: a; var: [nothing]
void	add_ent(t_env *e, char *key, char *val)
{
	t_var		*curr;

	curr = e->exp;
	while (curr->next)
		curr = curr->next;
	e->last_exp_id += 1;
	curr->id = e->last_exp_id;
	curr->key = key;
	curr->value = val;
	curr->next = gb_malloc(sizeof(t_var));
	curr->next->next = NULL;
	if (val == NULL)
		return ;
	curr = e->var;
	while (curr->next)
		curr = curr->next;
	e->last_var_id += 1;
	curr->id = e->last_var_id;
	curr->key = key;
	curr->value = val;
	curr->next = gb_malloc(sizeof(t_var));
	curr->next->next = NULL;
}

// char **split_ent(char *str)
// {
// 	char	**split;

// 	if (str == NULL)
// 		return (NULL);
// 	split = gb_malloc(sizeof(char *) * 2);
// 	split[0] = ft_strndup(str, find_pos(str, '='));
// 	if (split[0] == NULL)
// 	{
// 		split[0] = ft_strndup(str, find_pos(str, '\0'));
// 		split[1] = NULL;
// 		return (split);
// 	}
// 	split[1] = ft_strndup(str + find_pos(str, '=') + 1, find_pos(str, '\0'));
// 	return (split);
// }

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

// void	set_val(t_env *e, char *key, char *val)
// {
// 	t_var	*curr;

// 	curr = e->exp;
// 	while (curr->next)
// 	{
// 		if (ft_strcmp(curr->key, key) == 0)
// 		{
// 			curr->value = val;
// 			break;
// 		}
// 		curr = curr->next;
// 	}
// 	curr = e->var;
// 	while (curr->next)
// 	{
// 		if (ft_strcmp(curr->key, key) == 0)
// 		{
// 			curr->value = val;
// 			return ;
// 		}
// 		curr = curr->next;
// 	}
// }

void ft_strncpy(char *dst, char *src, int len)
{
	int i;

	i = -1;
	while (++i < len && src[i])
		dst[i] = src[i];
	dst[i] = '\0';
}

// char	*fetch_val(char *key, t_env *e)
// {
// 	t_var	*curr;

// 	curr = e->var;
// 	while (curr->next)
// 	{
// 		if (ft_strcmp(curr->key, key) == 0)
// 			return (curr->value);
// 		curr = curr->next;
// 	}
// 	return (NULL);
// }

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
	arr = gb_malloc(sizeof(char *) * (size + 1));
	arr[size] = NULL;
	curr = var;
	size = -1;
	while (curr->next)
	{
		if (!curr->key || !curr->value)
			continue ;
		arr[++size] = gb_add(ft_strjoin(curr->key, "="));
		arr[size] = gb_add(ft_strjoin(arr[size], curr->value));
		curr = curr->next;
	}
	return (arr);
}
