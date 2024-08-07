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
	t_exec	exec;

	exec.seq = gb_malloc(6 * sizeof(t_token));
	exec.seq[0] = T_HERE_DOC;
	exec.seq[1] = T_PIPE;
	exec.seq[2] = T_REDOUT;
	exec.seq[3] = T_CMD;
	exec.seq[4] = T_CMD;

	exec.redirs = gb_malloc(3 * sizeof(t_redir));
	exec.redirs[0].type = T_HERE_DOC;
	exec.redirs[0].file = "EOF";
	exec.redirs[1].type = T_PIPE;
	exec.redirs[1].file = NULL;
	exec.redirs[2].type = T_REDOUT;
	exec.redirs[2].file = "out.txt";

	exec.cmds = gb_malloc(2 * sizeof(t_cmd));
	exec.cmds[0].cmd = "cat";
	exec.cmds[0].argv = gb_malloc(3 * sizeof(char *));
	exec.cmds[0].argv[0] = "cat";
	exec.cmds[0].argv[1] = "-e";
	exec.cmds[0].argv[2] = NULL;
	exec.cmds[1].cmd = "grep";
	exec.cmds[1].argv = gb_malloc(4 * sizeof(char *));
	exec.cmds[1].argv[0] = "grep";
	exec.cmds[1].argv[1] = "lol";
	exec.cmds[1].argv[2] = "-v";

	gb_clear();
}
