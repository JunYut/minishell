/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:58:21 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/09 16:59:37 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_path	get_path(char *cmd, t_minishell *vars)
{
	char	*full_cmd;

	if (ft_strnstr(cmd, "/", ft_strlen(cmd)) || is_valid_path(vars->env->envp) == false)
		return ((t_path){check_exec(cmd), cmd});
	if (*cmd == '\0')
		return ((t_path){(t_err){ERRNO_NOT_FOUND, ERR_MSG_CMD_NOT_FOUND, "''"},
			NULL});
	full_cmd = parse_path(vars->env->envp, cmd);
	if (full_cmd != NULL)
		return ((t_path){(t_err){ERRNO_SUCCESS, -1, NULL}, full_cmd});
	return ((t_path){(t_err){ERRNO_NOT_FOUND,
		ERR_MSG_CMD_NOT_FOUND, cmd}, NULL});
}

bool	is_valid_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (envp[i] == NULL)
		return (false);
	return (true);
}
