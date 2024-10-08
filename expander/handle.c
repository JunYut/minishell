/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:21:12 by tjun-yu           #+#    #+#             */
/*   Updated: 2024/09/25 09:40:51 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char	*handle_reg_str(char *str, int *i)
{
	int		start;

	start = *i;
	while (str[*i] != '\0' && str[*i] != '\''
		&& str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*handle_squote(char *str, int *i)
{
	int		start;

	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i])
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*handle_dquote_str(char *str, int *i)
{
	int		start;

	start = *i;
	while (str[*i] && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*handle_dquote(char *str, int *i, t_minishell *vars)
{
	char	*ret_str;
	char	*tmp;

	ret_str = ft_strdup("\"");
	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
			tmp = handle_dollar(str, i, vars);
		else
			tmp = handle_dquote_str(str, i);
		ret_str = gnl_strjoin(ret_str, tmp);
		free(tmp);
	}
	if (str[*i])
		(*i)++;
	return (gnl_strjoin(ret_str, "\""));
}

char	*handle_dollar(char *str, int *i, t_minishell *vars)
{
	int		start;
	char	*val;
	char	*env_val;

	(*i)++;
	if (str[*i] && (str[*i] == '\0' || str[*i] == '"' || str[*i] == ' '))
		return (ft_strdup("$"));
	start = *i;
	if (str[*i] == '?' || is_valid_var_char(str[*i]) == false)
	{
		(*i)++;
		if (str[*i - 1] == '?')
			return (ft_itoa(vars->exit_status));
		if (is_valid_var_char(str[*i - 1]) == false)
			return (ft_substr(str, start - 1, *i - start + 1));
	}
	while (is_valid_var_char(str[*i]) == true)
		(*i)++;
	val = ft_substr(str, start, *i - start);
	env_val = fetch_val(val, vars->env);
	if (env_val == NULL)
		return (free(val), ft_strdup(""));
	return (free(val), ft_strdup(env_val));
}
