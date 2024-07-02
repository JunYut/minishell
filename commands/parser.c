# include "parser.h"
# include "utils.h"
# include "libft.h"
# include "debug.h"

// will not handle '*', quotes and subshells
t_cmd	*parse(t_token *tokens, char **identifiers, char *envp[])
{
	t_cmd	*cmd_args;
	// int		cmd_c;
	// int		arg_c;
	int		i;

	// count number of commands & args
		// loop to first operator, record position
		// go back until first identifier (before is operator/is first)
		// increment cmd count
		// loop to operator, increment args count at the same time
	i = -1;
	while (tokens[++i] != T_INVALID)
	{
		// while (tokens[i] != T_INVALID && !is_operator(tokens[i]))
		// {
			
		// }
	}
	// append full path to command
		// loop to first operator, record position
		// go back until first identifier (before is operator/is first)
		// set cmd path
		// loop to operator, set args at the same time
	(void)tokens;
	(void)identifiers;
	(void)envp;
	(void)cmd_args;
	return (NULL);
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
	path = find_bin(path_list);
	free_2d((void **)path_list);
	return (path);
}

char	*find_bin(char **path_list)
{
	int	i;

	i = -1;
	while (path_list[++i])
		if (is_cmd(path_list[i]))
			return (ft_strdup(path_list[i]));
	return (NULL);
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
