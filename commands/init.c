# include "commands.h"

// temp function to init t_cmd struct
t_cmd	*init_cmd(const char *raw)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	cmd->identifiers = ft_split(raw, ' ');	// Not legit
	cmd->tokens = tokenize(cmd->identifiers);
	return (cmd);
}

t_token_type	*tokenize(char **identifiers)
{
	t_token_type	*tokens;
	int				count;

	count = -1;
	while (identifiers[++count]);
	tokens = (t_token_type *)ft_calloc(count + 1, sizeof(t_token_type));
	tokens[count] = -1;
	while (--count > 0)
	{
		if (ft_strncmp(identifiers[count], ">", 1) == 0)
			tokens[count] = T_REDIRECT_OUT;
		else if (ft_strncmp(identifiers[count], "<", 1) == 0)
			tokens[count] = T_REDIRECT_IN;
		else if (ft_strncmp(identifiers[count], "<<", 2) == 0)
			tokens[count] = T_HERE_DOC;
		else if (ft_strncmp(identifiers[count], ">>", 2) == 0)
			tokens[count] = T_APPEND;
		else if (ft_strncmp(identifiers[count], "|", 1) == 0)
			tokens[count] = T_PIPE;
		else if (ft_strncmp(identifiers[count], "(", 1) == 0)
			tokens[count] = T_L_PAREN;
		else if (ft_strncmp(identifiers[count], ")", 1) == 0)
			tokens[count] = T_R_PAREN;
		else if (ft_strncmp(identifiers[count], "||", 2) == 0)
			tokens[count] = T_OR;
		else if (ft_strncmp(identifiers[count], "&&", 2) == 0)
			tokens[count] = T_AND;
		else if (ft_strncmp(identifiers[count], "\\n", 1) == 0)
			tokens[count] = T_NEWLINE;
		else
			tokens[count] = T_ARG;
	}
	return (tokens);
}
