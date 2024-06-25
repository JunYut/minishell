/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:00:59 by we                #+#    #+#             */
/*   Updated: 2024/06/25 16:15:02 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "commands.h"

t_cmd	*new_cmd(const char *line)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	cmd->raw = ft_strdup(line);
	cmd->argv = ft_split(line, ' ');
	return (cmd);
}

void	free_cmd(void *cmd)
{
	t_cmd	*tmp;

	if (!cmd)
		return ;
	tmp = (t_cmd *)cmd;
	free(tmp->raw);
	free(tmp->type);
	ft_free_s_arr(tmp->argv);
}
