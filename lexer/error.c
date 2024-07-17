/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:39:59 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/16 17:18:31 by kkhai-ki         ###   ########.fr       */
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

void	handle_quote_err(char quote, t_minishell *vars)
{
	char	*buffer;
	char	*appended_str;

	(void)quote;
	(void)vars;
	buffer = NULL;
	appended_str = ft_strdup("");
	while (is_in_set(quote, buffer) == 0)
	{
		buffer = readline("> ");
		appended_str = ft_strjoin_delim(appended_str, buffer, "\n");
	}
	printf("%s\n", appended_str);
}
