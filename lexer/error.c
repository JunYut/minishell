/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:39:59 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/17 23:43:08 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quote_err(char quote, t_minishell *vars)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
	ft_putchar_fd(quote, 2);
	ft_putstr_fd("'\n", 2);
	set_parse_err_type(vars, E_EOF);
	vars->exit_status = 2;
}

void	handle_open_quote(char **line, char **buffer, int *char_count, char quote)
{
	char	*read_line;
	char	*appended_str;
	char	*trimmed_str;

	read_line = NULL;
	appended_str = ft_strdup(*line);
	while (is_quote_balance(appended_str, quote) == false)
	{
		read_line = readline("> ");
		if (read_line == NULL)
			break ;
		appended_str = ft_strjoin_delim(appended_str, read_line, "\n");
	}
	if (read_line != NULL)
		trimmed_str = ft_trim_str(appended_str, quote);
	else
		trimmed_str = appended_str;
	(*char_count) = ft_strlen(trimmed_str);
	*line = appended_str;
	*buffer = appended_str;
}

bool	is_quote_balance(char *str, char quote)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == quote)
			count++;
		str++;
	}
	if (count != 0 && count % 2 == 0)
		return (true);
	else
		return (false);
}
