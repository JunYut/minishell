# include "exec.h"
# include "pipe.h"
# include "redir.h"
# include "env.h"
# include "signal.h"
# include "libft.h"
# include "gbc.h"
# include "define.h"

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	t_env	*e = dup_env(envp);
	t_cmd_line	cmd;

	cmd.redirs = gb_malloc(4 * sizeof(t_redir));
	cmd.redirs[0].type = T_HERE_DOC;
	cmd.redirs[0].file = "EOF";
	cmd.redirs[1].type = T_PIPE;
	cmd.redirs[1].file = NULL;
	cmd.redirs[2].type = T_REDOUT;
	cmd.redirs[2].file = "out.txt";
	cmd.redirs[3].type = T_END;
	cmd.redirs[3].file = NULL;

	cmd.cmds = gb_malloc(3 * sizeof(t_cmd));
	cmd.cmds[0].cmd = "/usr/bin/cat";
	cmd.cmds[0].argv = gb_malloc(3 * sizeof(char *));
	cmd.cmds[0].argv[0] = "cat";
	cmd.cmds[0].argv[1] = "-e";
	cmd.cmds[0].argv[2] = NULL;
	cmd.cmds[1].cmd = "/usr/bin/grep";
	cmd.cmds[1].argv = gb_malloc(4 * sizeof(char *));
	cmd.cmds[1].argv[0] = "grep";
	cmd.cmds[1].argv[1] = "lol";
	cmd.cmds[1].argv[2] = "-v";
	cmd.cmds[1].argv[3] = NULL;
	cmd.cmds[2].cmd = NULL;
	cmd.cmds[2].argv = NULL;

	cmd_exec(&cmd, e);

	gb_clear();
}
