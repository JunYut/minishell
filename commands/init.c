# include "commands.h"
# include "parser.h"
# include "tokenizer.h"
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
