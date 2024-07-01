# include "commands.h"
# include "parser.h"
# include "utils.h"
# include "debug.h"

// assumes that raw is a valid command line
t_cmd_line	*init_cmd(const char *raw, char *envp[])
{
	t_cmd_line	*cmd;

	cmd = (t_cmd_line *)ft_calloc(1, sizeof(t_cmd_line));
	cmd->identifiers = ft_split(raw, ' ');	// Not legit
	cmd->tokens = tokenize(cmd->identifiers);
	cmd->cmds = parse(cmd->tokens, cmd->identifiers, envp);
	return (cmd);
}

// will not handle '*', quotes and subshells
t_cmd	*parse(t_token *tokens, char **identifiers, char *envp[])
{
	t_cmd	*cmd_args;

	// append full path to command
	// count number of commands
	// count number of arguments for each command
	(void)tokens;
	(void)identifiers;
	(void)envp;
	(void)cmd_args;
	return (NULL);
}

// only works if command line is split by spaces
t_token	*tokenize(char **identifiers)
{
	t_token	*tokens;
	int				count;

	count = -1;
	while (identifiers[++count]);
	tokens = (t_token *)ft_calloc(count + 1, sizeof(t_token));
	tokens[count] = T_INVALID;
	while (--count >= 0)
	{
		if (ft_strncmp(identifiers[count], "<<", 2) == 0)
			tokens[count] = T_HERE_DOC;
		else if (ft_strncmp(identifiers[count], ">>", 2) == 0)
			tokens[count] = T_APPEND;
		else if (ft_strncmp(identifiers[count], ">", 1) == 0)
			tokens[count] = T_REDIRECT_OUT;
		else if (ft_strncmp(identifiers[count], "<", 1) == 0)
			tokens[count] = T_REDIRECT_IN;
		else if (ft_strncmp(identifiers[count], "||", 2) == 0)
			tokens[count] = T_OR;
		else if (ft_strncmp(identifiers[count], "&&", 2) == 0)
			tokens[count] = T_AND;
		else if (ft_strncmp(identifiers[count], "|", 1) == 0)
			tokens[count] = T_PIPE;
		else if (ft_strncmp(identifiers[count], "(", 1) == 0)
			tokens[count] = T_L_PAREN;
		else if (ft_strncmp(identifiers[count], ")", 1) == 0)
			tokens[count] = T_R_PAREN;
		else if (ft_strncmp(identifiers[count], "\\n", 1) == 0)
			tokens[count] = T_NEWLINE;
		else
			tokens[count] = T_IDEN;
	}
	return (tokens);
}
