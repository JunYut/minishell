# include "exec.h"
# include "signal.h"
# include "gbc.h"
# include "define.h"

# define TEST 2

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	t_env	*e = dup_env(envp);
	t_cmd_line	cmd;

	// cat -e define.h
	# if TEST == 1
	cmd.seq_count = 1;
	cmd.seq = gb_malloc(sizeof(t_pipe) * 1);
	cmd.pid = gb_malloc(sizeof(pid_t) * 1);
	cmd.seq[0].type = T_PIPE;
		cmd.seq[0].cmd_count = 1;
		cmd.seq[0].pipe_count = 0;
		cmd.seq[0].cmd = gb_malloc(sizeof(t_cmd) * 2);
			cmd.seq[0].cmd[0].cmd = "/usr/bin/cat";
			cmd.seq[0].cmd[0].argv = (char *[]){"cat", "-e", NULL};
			cmd.seq[0].cmd[0].file = NULL;
	# endif
	// cat -e define.h > out.txt
	# if TEST == 2
	cmd.seq_count = 1;
	cmd.seq = gb_malloc(sizeof(t_pipe) * 1);
	cmd.pid = gb_malloc(sizeof(pid_t) * 1);
	cmd.seq[0].type = T_PIPE;
		cmd.seq[0].cmd_count = 1;
		cmd.seq[0].pipe_count = 0;
		cmd.seq[0].cmd = gb_malloc(sizeof(t_cmd) * 2);
			cmd.seq[0].cmd[0].cmd = "/usr/bin/cat";
			cmd.seq[0].cmd[0].argv = (char *[]){"cat", "-e", NULL};
			cmd.seq[0].cmd[0].file = gb_malloc(sizeof(t_file) * 1);
				cmd.seq[0].cmd[0].file[0].type = T_REDOUT;
				cmd.seq[0].cmd[0].file[0].file = "out.txt";
	# endif
	// echo hello | cat -e | tr h H || echo goodbye | cat -e | tr o e && echo wait | cat -e | tr w t
	# if TEST == 2
	cmd.seq_count = 3;
	cmd.seq = gb_malloc(sizeof(t_pipe) * 4);
	cmd.pid = gb_malloc(sizeof(pid_t) * 4);
	cmd.seq[0].type = T_PIPE;
		cmd.seq[0].cmd_count = 3;
		cmd.seq[0].pipe_count = 2;
		cmd.seq[0].cmd = gb_malloc(sizeof(t_cmd) * 3);
			cmd.seq[0].cmd[0].cmd = "/bin/echo";
			cmd.seq[0].cmd[0].argv = (char *[]){"echo", "hello", NULL};
			cmd.seq[0].cmd[0].file = NULL;
			cmd.seq[0].cmd[1].cmd = "/bin/cat";
			cmd.seq[0].cmd[1].argv = (char *[]){"cat", "-e", NULL};
			cmd.seq[0].cmd[1].file = NULL;
			cmd.seq[0].cmd[2].cmd = "/usr/bin/tr";
			cmd.seq[0].cmd[2].argv = (char *[]){"tr", "h", "H", NULL};
			cmd.seq[0].cmd[2].file = NULL;
	cmd.seq[1].type = T_OR;
		cmd.seq[1].cmd_count = 3;
		cmd.seq[1].pipe_count = 2;
		cmd.seq[1].cmd = gb_malloc(sizeof(t_cmd) * 3);
			cmd.seq[1].cmd[0].cmd = "/bin/echo";
			cmd.seq[1].cmd[0].argv = (char *[]){"echo", "goodbye", NULL};
			cmd.seq[1].cmd[0].file = NULL;
			cmd.seq[1].cmd[1].cmd = "/bin/cat";
			cmd.seq[1].cmd[1].argv = (char *[]){"cat", "-e", NULL};
			cmd.seq[1].cmd[1].file = NULL;
			cmd.seq[1].cmd[2].cmd = "/usr/bin/tr";
			cmd.seq[1].cmd[2].argv = (char *[]){"tr", "o", "e", NULL};
			cmd.seq[1].cmd[2].file = NULL;
	cmd.seq[2].type = T_AND;
		cmd.seq[2].cmd_count = 3;
		cmd.seq[2].pipe_count = 2;
		cmd.seq[2].cmd = gb_malloc(sizeof(t_cmd) * 3);
			cmd.seq[2].cmd[0].cmd = "/bin/echo";
			cmd.seq[2].cmd[0].argv = (char *[]){"echo", "wait", NULL};
			cmd.seq[2].cmd[0].file = NULL;
			cmd.seq[2].cmd[1].cmd = "/bin/cat";
			cmd.seq[2].cmd[1].argv = (char *[]){"cat", "-e", NULL};
			cmd.seq[2].cmd[1].file = NULL;
			cmd.seq[2].cmd[2].cmd = "/usr/bin/tr";
			cmd.seq[2].cmd[2].argv = (char *[]){"tr", "w", "t", NULL};
			cmd.seq[2].cmd[2].file = NULL;
	# endif

	exec(&cmd, e);

	return (0);
}
