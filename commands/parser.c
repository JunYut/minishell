# include "parser.h"
# include "commands.h"
# include "utils.h"
# include "libft.h"
# include "debug.h"

// will not handle '*', quotes and subshells
t_cmd	*parse(t_token *tokens, char **identifiers, char *envp[])
{
	t_cmd	*cmd_args;
	int		cmd_c;
	int		arg_c;
	int		i;
	int		j;

	cmd_c = 0;
	i = -1;
	while (tokens[++i] != T_INVALID)
		if (tokens[i] == T_CMD)
			cmd_c++;
	printf("cmd_c: %d\n", cmd_c);	// DEBUG
	cmd_args = (t_cmd *)ft_calloc(cmd_c + 1, sizeof(t_cmd));
	cmd_args[cmd_c].cmd = NULL;
	i = -1;
	while (tokens[++i] != T_INVALID)
	{
		arg_c = 0;
		if (tokens[i] == T_CMD)
		{
			printf("i: %d\n", i);	// DEBUG
			printf("cmd: %s\n", identifiers[i]);	// DEBUG
			cmd_args[i].cmd = parse_path(envp, identifiers[i]);
			printf("cmd: %s\n", cmd_args[i].cmd);	// DEBUG
			j = i;
			while (tokens[++j] == T_ARG)
				arg_c++;
			printf("arg_c: %d\n", arg_c);	// DEBUG
			cmd_args[i].args = (char **)ft_calloc(arg_c + 1, sizeof(char *));
			cmd_args[i].args[arg_c] = NULL;
			j = i;
			while (tokens[++j] == T_ARG)
			{
				// printf("identifiers[%d]: %s\n", j, identifiers[j]);	// DEBUG
				cmd_args[i].args[j - i - 1] = ft_strdup(identifiers[j]);
			}
		}
	}
	printf("cmd_args[0].cmd: %s\n", cmd_args[0].cmd);	// DEBUG
	print_arr(cmd_args[0].args);	// DEBUG
	printf("cmd_args[1].cmd: %s\n", cmd_args[1].cmd);	// DEBUG
	print_arr(cmd_args[1].args);	// DEBUG
	printf("\n");	// DEBUG
	return (cmd_args);
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
		if (access(path_list[i], X_OK) == 0)
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
