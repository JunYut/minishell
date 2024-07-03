# include "parser.h"
# include "commands.h"
# include "utils.h"
# include "libft.h"
# include "debug.h"

// will not handle '*', quotes and subshells
t_cmd	*parse_cmd(t_token *tokens, char **identifiers, char *envp[])
{
	t_cmd	*cmds;
	int		cmd_c;
	int		i;
	int		j;
	int		k;

	cmd_c = 0;
	i = -1;
	while (tokens[++i] != T_INVALID)
		if (tokens[i] == T_CMD)
			cmd_c++;
	cmds = (t_cmd *)ft_calloc(cmd_c + 1, sizeof(t_cmd));
	cmds[cmd_c].cmd = NULL;
	j = -1;
	i = -1;
	while (tokens[++i] != T_INVALID)
	{
		if (tokens[i] != T_CMD)
			continue ;
		cmds[++j].cmd = parse_path(envp, identifiers[i]);
		cmds[j].argc = 0;
		k = i;
		while (tokens[++k] == T_ARG)
			cmds[j].argc++;
		cmds[j].args = (char **)ft_calloc(cmds[j].argc + 1, sizeof(char *));
		cmds[j].args[cmds[j].argc] = NULL;
		k = i;
		while (tokens[++k] == T_ARG)
			cmds[j].args[k - i - 1] = ft_strdup(identifiers[k]);
	}
	return (cmds);
}

// returns full path to command (allocated)
char	*parse_path(char *envp[], char *cmd)
{
	char	**path_list;
	char	*path;
	int		i;

	i = -1;
	while (envp[++i] && ft_strncmp(envp[i], "PATH=", 5))
		;
	path_list = ft_split(envp[i], ':');
	prepend_cmd(path_list, cmd);
	trim_path(path_list[0], "PATH=");
	path = NULL;
	i = -1;
	while (path_list[++i] && !path)
		if (access(path_list[i], X_OK) == 0)	// not considering directories
			path = ft_strdup(path_list[i]);
	free_2d((void **)path_list);
	return (path);
}

void	trim_path(char *cmd, char *path)
{
	size_t	path_len;

	path_len = ft_strlen(path);
	ft_memmove(cmd, cmd + path_len, ft_strlen(cmd) - path_len);
	cmd[ft_strlen(cmd) - path_len] = '\0';
}

void	prepend_cmd(char **path_list, char *cmd)
{
	int	i;

	i = -1;
	while (path_list[++i])
	{
		path_list[i] = gnl_strjoin(path_list[i], "/");
		path_list[i] = gnl_strjoin(path_list[i], cmd);
	}
}
