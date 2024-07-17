/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:39:59 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/17 13:32:22 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	handle_quote_err(char quote, t_minishell *vars)
// {
// 	ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
// 	ft_putchar_fd(quote, 2);
// 	ft_putstr_fd("'\n", 2);
// 	vars->exit_status = 2;
// }

void	handle_quote_err(char **str, int *char_count, char quote)
{
	char	*buffer;
	char	*appended_str;

	buffer = NULL;
	appended_str = ft_strdup(*str);
	while (is_in_set(quote, buffer) == 0)
	{
		buffer = readline("> ");
		appended_str = ft_strjoin_delim(appended_str, buffer, "\n");
	}
	(*char_count) = (ft_strlen(appended_str) + ft_strlen(*str));
	*str = appended_str;
}
