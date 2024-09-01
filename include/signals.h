/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:57:18 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/30 10:25:00 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

/*
Allowed functions:  signal, sigaction, sigemptyset, sigaddset

Non-interactive mode:
- ctrl-C displays '^C' then a new prompt on a new line.
- ctrl-D does nothing (no need to implement this).
- ctrl-\ displays '^\Quit: 3' then a new prompt on a new line.

Interactive mode(involves real-time user input by shell builtins):
- ctrl-C displays a new prompt on a new line.
- ctrl-D exits interactive mode. (no need to implement this)
- ctrl-\ does nothing.

Interactive actions in bash:  prompt, read, <<heredoc, unclosed quotes
Interactive actions in minishell: prompt, <<heredoc, unclosed quotes
*/

# include <signal.h>
# include <readline/readline.h>
# include <stdio.h>
# include "define.h"

void	int_sigint(int sig);
void	int_sigquit(int sig);
