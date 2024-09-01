/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:56:46 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/30 10:28:27 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "signals.h"

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
	// if (!g_wait)
	printf("Quit\n");
}
