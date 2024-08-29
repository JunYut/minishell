/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:39:59 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/29 11:58:22 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

// multiple definition
void	handle_quote_err(char quote, t_minishell *vars)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
	ft_putchar_fd(quote, 2);
	ft_putstr_fd("'\n", 2);
	ft_putendl_fd("minishell: syntax error: unexpected end of file", 2);
	set_parse_err_type(vars, E_EOF);
	vars->exit_status = 2;
}

// multiple definition
void	handle_open_quote(char **line, char **buffer, int *char_count, char quote)
{
	char	*read_line;
	char	*appended_str;
	char	*trimmed_str;

	// printf("quote type: %c\n", quote);
	read_line = NULL;
	appended_str = ft_strdup(*line);
	while (is_quote_balance(appended_str, quote) == false)
	{
		read_line = readline("> ");
		if (read_line == NULL)
			break ;
		appended_str = ft_strjoin_delim(appended_str, read_line, "\n");
	}
	// if (read_line != NULL)
		trimmed_str = ft_trim_str(appended_str, quote);
	// else
	// 	trimmed_str = appended_str;
	// printf("trimmed: %s\n", trimmed_str);
	*char_count = ft_strlen(trimmed_str);
	*line = appended_str;
	*buffer = appended_str;
	// printf("char_count: %d\n", *char_count);
}

// multiple definition
bool	is_quote_balance(char *str, char quote)
{
	int	count;

	// printf("string: %s\n\n", str);
	// printf("quote type: %c\n\n", quote);
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
