/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:00:59 by we                #+#    #+#             */
/*   Updated: 2024/06/26 10:37:38 by tjun-yu          ###   ########.fr       */
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

int	*tokenize(const char *argv[])
{
	int	*type;
	int	i;

	i = -1;
	while (argv[++i]);
	type = (int *)ft_calloc(i, sizeof(int));
	i = -1;
	while (argv[++i])
	{
		if (access(argv[i], F_OK) == -1)
			continue ;
		if (access(argv[i], X_OK) == 0)
			type[i] = CMD;
		else if (ft_strncmp(argv[i], "-", 1) == 0)
			type[i] = OPTION;
		else if (is_operator(argv[i]))
			type[i] = OPERATOR;
		else
			type[i] = ARG;

	}
	return (type);
}

int	is_operator(const char *line)
{
	if (ft_strncmp(line, ">>" , 2) == 0)
		return (1);
	if (ft_strncmp(line, "<", 1) == 0)
		return (1);
	if (ft_strncmp(line, ">", 1) == 0)
		return (1);
	if (ft_strncmp(line, "|", 1) == 0)
		return (1);
	if (ft_strncmp(line, "&&", 2) == 0)
		return (1);
	if (ft_strncmp(line, "||", 2) == 0)
		return (1);
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
