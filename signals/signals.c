/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:56:46 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/11 12:23:04 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "minishell.h"

void	heredoc_sigint(int sig)
{
	(void)sig;
	free(init_vars(NULL, NULL)->doc);
	clear(init_vars(NULL, NULL));
	exit(130);
}

void	int_sigint(int sig)
{
	(void)sig;
	printf("\n");
	if (!g_wait)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	int_sigquit(int sig)
{
	(void)sig;
	if (g_wait)
		ft_putstr_fd("Quit\n", STDERR_FILENO);
}
