# include "exec.h"
# include "signals.h"
# include "env.h"
# include "gbc.h"
# include "define.h"

volatile sig_atomic_t	g_wait;

# define TEST 9

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	t_env	*e = dup_env(envp);
	t_cmd_line	cmd;

	signal(SIGINT, int_sigint);
	signal(SIGQUIT, int_sigquit);

	// cat -e define.h
	# if TEST == 1
	cmd.seq_count = 1;
	cmd.pid = gb_malloc(sizeof(pid_t) * 1);
	cmd.seq = gb_malloc(sizeof(t_pipe) * 1);
	cmd.seq[0].type = T_PIPE;
		cmd.seq[0].cmd_count = 1;
		cmd.seq[0].pipe_count = 0;
		cmd.seq[0].pid = gb_malloc(sizeof(pid_t) * 1);
		cmd.seq[0].cmd = gb_malloc(sizeof(t_cmd) * 1);
			cmd.seq[0].cmd[0].cmd = "/usr/bin/cat";
			cmd.seq[0].cmd[0].argv = (char *[]){"cat", "-e", "define.h", NULL};
			cmd.seq[0].cmd[0].file_count = 0;
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
		cmd.seq[0].pid = gb_malloc(sizeof(pid_t) * 1);
		cmd.seq[0].cmd = gb_malloc(sizeof(t_cmd) * 2);
			cmd.seq[0].cmd[0].cmd = "/usr/bin/cat";
			cmd.seq[0].cmd[0].argv = (char *[]){"cat", "-e", "define.h", NULL};
			cmd.seq[0].cmd[0].file_count = 1;
			cmd.seq[0].cmd[0].file = gb_malloc(sizeof(t_file) * 1);
				cmd.seq[0].cmd[0].file[0].type = T_REDOUT;
				cmd.seq[0].cmd[0].file[0].file = "out.txt";
	# endif
	// cat -e define.h | tail -n 7
	# if TEST == 3
	cmd.seq_count = 1;
	cmd.pid = gb_malloc(sizeof(pid_t) * 1);
	cmd.seq = gb_malloc(sizeof(t_pipe) * 1);
	cmd.seq[0].type = T_PIPE;
		cmd.seq[0].cmd_count = 2;
		cmd.seq[0].pipe_count = 1;
		cmd.seq[0].pid = gb_malloc(sizeof(pid_t) * 2);
		cmd.seq[0].pipefd = gb_malloc(sizeof(int *) * 1);
			cmd.seq[0].pipefd[0] = gb_malloc(sizeof(int) * 2);
		cmd.seq[0].cmd = gb_malloc(sizeof(t_cmd) * 2);
			cmd.seq[0].cmd[0].cmd = "/usr/bin/cat";
			cmd.seq[0].cmd[0].argv = (char *[]){"cat", "-e", "define.h", NULL};
			cmd.seq[0].cmd[0].file_count = 0;
			cmd.seq[0].cmd[0].file = NULL;
			cmd.seq[0].cmd[1].cmd = "/usr/bin/tail";
			cmd.seq[0].cmd[1].argv = (char *[]){"tail", "-n", "8", NULL};
			cmd.seq[0].cmd[1].file_count = 0;
			cmd.seq[0].cmd[1].file = NULL;
	# endif
	// cat -e define.h && echo success
	# if TEST == 4
	cmd.seq_count = 2;
	cmd.pid = gb_malloc(sizeof(pid_t) * 2);
	cmd.seq = gb_malloc(sizeof(t_pipe) * 2);
	cmd.seq[0].type = T_PIPE;
		cmd.seq[0].cmd_count = 1;
		cmd.seq[0].pipe_count = 0;
		cmd.seq[0].pid = gb_malloc(sizeof(pid_t) * 1);
		cmd.seq[0].cmd = gb_malloc(sizeof(t_cmd) * 1);
			cmd.seq[0].cmd[0].cmd = "/usr/bin/cat";
			cmd.seq[0].cmd[0].argv = (char *[]){"cat", "-e", "define.h", NULL};
			cmd.seq[0].cmd[0].file_count = 0;
			cmd.seq[0].cmd[0].file = NULL;
	cmd.seq[1].type = T_AND;
		cmd.seq[1].cmd_count = 1;
		cmd.seq[1].pipe_count = 0;
		cmd.seq[1].pid = gb_malloc(sizeof(pid_t) * 1);
		cmd.seq[1].cmd = gb_malloc(sizeof(t_cmd) * 1);
			cmd.seq[1].cmd[0].cmd = "/bin/echo";
			cmd.seq[1].cmd[0].argv = (char *[]){"echo", "success", NULL};
			cmd.seq[1].cmd[0].file_count = 0;
			cmd.seq[1].cmd[0].file = NULL;
	# endif
	// cat -e define.h || echo fail
	# if TEST == 5
	cmd.seq_count = 2;
	cmd.pid = gb_malloc(sizeof(pid_t) * 2);
	cmd.seq = gb_malloc(sizeof(t_pipe) * 2);
	cmd.seq[0].type = T_PIPE;
		cmd.seq[0].cmd_count = 1;
		cmd.seq[0].pipe_count = 0;
		cmd.seq[0].pid = gb_malloc(sizeof(pid_t) * 1);
		cmd.seq[0].cmd = gb_malloc(sizeof(t_cmd) * 1);
			cmd.seq[0].cmd[0].cmd = "/usr/bin/cat";
			cmd.seq[0].cmd[0].argv = (char *[]){"cat", "-e", "define.h", NULL};
			cmd.seq[0].cmd[0].file_count = 0;
			cmd.seq[0].cmd[0].file = NULL;
	cmd.seq[1].type = T_OR;
		cmd.seq[1].cmd_count = 1;
		cmd.seq[1].pipe_count = 0;
		cmd.seq[1].pid = gb_malloc(sizeof(pid_t) * 1);
		cmd.seq[1].cmd = gb_malloc(sizeof(t_cmd) * 1);
			cmd.seq[1].cmd[0].cmd = "/bin/echo";
			cmd.seq[1].cmd[0].argv = (char *[]){"echo", "fail", NULL};
			cmd.seq[1].cmd[0].file_count = 0;
			cmd.seq[1].cmd[0].file = NULL;
	# endif
	// cat -e define.h > 1.txt > 2.txt > out.txt
	# if TEST == 6
	cmd.seq_count = 1;
	cmd.pid = gb_malloc(sizeof(pid_t) * 1);
	cmd.seq = gb_malloc(sizeof(t_pipe) * 1);
		cmd.seq[0].type = T_PIPE;
		cmd.seq[0].cmd_count = 1;
		cmd.seq[0].pipe_count = 0;
		cmd.seq[0].pid = gb_malloc(sizeof(pid_t) * 1);
		cmd.seq[0].cmd = gb_malloc(sizeof(t_cmd) * 1);
			cmd.seq[0].cmd[0].cmd = "/usr/bin/cat";
			cmd.seq[0].cmd[0].argv = (char *[]){"cat", "-e", "define.h", NULL};
			cmd.seq[0].cmd[0].file_count = 3;
			cmd.seq[0].cmd[0].file = gb_malloc(sizeof(t_file) * 3);
				cmd.seq[0].cmd[0].file[0].type = T_REDOUT;
				cmd.seq[0].cmd[0].file[0].file = "1.txt";
				cmd.seq[0].cmd[0].file[1].type = T_REDOUT;
				cmd.seq[0].cmd[0].file[1].file = "2.txt";
				cmd.seq[0].cmd[0].file[2].type = T_REDOUT;
				cmd.seq[0].cmd[0].file[2].file = "out.txt";
	# endif
	// cat -e define.h | tail -n 8 | tr # @ | grep define
	# if TEST == 7
	cmd.seq_count = 1;
	cmd.pid = gb_malloc(sizeof(pid_t) * 1);
	cmd.seq = gb_malloc(sizeof(t_pipe) * 1);
	cmd.seq[0].type = T_PIPE;
		cmd.seq[0].cmd_count = 4;
		cmd.seq[0].pipe_count = 3;
		cmd.seq[0].pid = gb_malloc(sizeof(pid_t) * 4);
		cmd.seq[0].pipefd = gb_malloc(sizeof(int *) * 3);
			cmd.seq[0].pipefd[0] = gb_malloc(sizeof(int) * 2);
			cmd.seq[0].pipefd[1] = gb_malloc(sizeof(int) * 2);
			cmd.seq[0].pipefd[2] = gb_malloc(sizeof(int) * 2);
		cmd.seq[0].cmd = gb_malloc(sizeof(t_cmd) * 4);
			cmd.seq[0].cmd[0].cmd = "/usr/bin/cat";
			cmd.seq[0].cmd[0].argv = (char *[]){"cat", "-e", "define.h", NULL};
			cmd.seq[0].cmd[0].file_count = 0;
			cmd.seq[0].cmd[0].file = NULL;
			cmd.seq[0].cmd[1].cmd = "/usr/bin/tail";
			cmd.seq[0].cmd[1].argv = (char *[]){"tail", "-n", "8", NULL};
			cmd.seq[0].cmd[1].file_count = 0;
			cmd.seq[0].cmd[1].file = NULL;
			cmd.seq[0].cmd[2].cmd = "/usr/bin/tr";
			cmd.seq[0].cmd[2].argv = (char *[]){"tr", "#", "@", NULL};
			cmd.seq[0].cmd[2].file_count = 0;
			cmd.seq[0].cmd[2].file = NULL;
			cmd.seq[0].cmd[3].cmd = "/usr/bin/grep";
			cmd.seq[0].cmd[3].argv = (char *[]){"grep", "define", NULL};
			cmd.seq[0].cmd[3].file_count = 0;
			cmd.seq[0].cmd[3].file = NULL;
	# endif
	// cat -e < define.h | tail -n 8 | tr # @ | grep define > out.txt
	# if TEST == 8
	cmd.seq_count = 1;
	cmd.pid = gb_malloc(sizeof(pid_t) * 1);
	cmd.seq = gb_malloc(sizeof(t_pipe) * 1);
		cmd.seq[0].type = T_PIPE;
		cmd.seq[0].cmd_count = 4;
		cmd.seq[0].pipe_count = 3;
		cmd.seq[0].pid = gb_malloc(sizeof(pid_t) * 4);
		cmd.seq[0].pipefd = gb_malloc(sizeof(int *) * 3);
			cmd.seq[0].pipefd[0] = gb_malloc(sizeof(int) * 2);
			cmd.seq[0].pipefd[1] = gb_malloc(sizeof(int) * 2);
			cmd.seq[0].pipefd[2] = gb_malloc(sizeof(int) * 2);
		cmd.seq[0].cmd = gb_malloc(sizeof(t_cmd) * 4);
			cmd.seq[0].cmd[0].cmd = "/usr/bin/cat";
			cmd.seq[0].cmd[0].argv = (char *[]){"cat", "-e", NULL};
			cmd.seq[0].cmd[0].file_count = 1;
			cmd.seq[0].cmd[0].file = gb_malloc(sizeof(t_file) * 1);
				cmd.seq[0].cmd[0].file[0].type = T_REDIN;
				cmd.seq[0].cmd[0].file[0].file = "define.h";
			cmd.seq[0].cmd[1].cmd = "/usr/bin/tail";
			cmd.seq[0].cmd[1].argv = (char *[]){"tail", "-n", "8", NULL};
			cmd.seq[0].cmd[1].file_count = 0;
			cmd.seq[0].cmd[1].file = NULL;
			cmd.seq[0].cmd[2].cmd = "/usr/bin/tr";
			cmd.seq[0].cmd[2].argv = (char *[]){"tr", "#", "@", NULL};
			cmd.seq[0].cmd[2].file_count = 0;
			cmd.seq[0].cmd[2].file = NULL;
			cmd.seq[0].cmd[3].cmd = "/usr/bin/grep";
			cmd.seq[0].cmd[3].argv = (char *[]){"grep", "define", NULL};
			cmd.seq[0].cmd[3].file_count = 1;
			cmd.seq[0].cmd[3].file = gb_malloc(sizeof(t_file) * 1);
				cmd.seq[0].cmd[3].file[0].type = T_REDOUT;
				cmd.seq[0].cmd[3].file[0].file = "out.txt";
	# endif
	// grep define < define.h | tr # @ > out.txt || echo fail
	# if TEST == 9
	cmd.seq_count = 2;
	cmd.pid = gb_malloc(sizeof(pid_t) * 2);
	cmd.seq = gb_malloc(sizeof(t_pipe) * 2);
		cmd.seq[0].type = T_PIPE;
		cmd.seq[0].cmd_count = 2;
		cmd.seq[0].pipe_count = 1;
		cmd.seq[0].pid = gb_malloc(sizeof(pid_t) * 2);
		cmd.seq[0].pipefd = gb_malloc(sizeof(int *) * 1);
			cmd.seq[0].pipefd[0] = gb_malloc(sizeof(int) * 2);
		cmd.seq[0].cmd = gb_malloc(sizeof(t_cmd) * 2);
			cmd.seq[0].cmd[0].cmd = "/usr/bin/grep";
			cmd.seq[0].cmd[0].argv = (char *[]){"grep", "define", NULL};
			cmd.seq[0].cmd[0].file_count = 1;
			cmd.seq[0].cmd[0].file = gb_malloc(sizeof(t_file) * 1);
				cmd.seq[0].cmd[0].file[0].type = T_REDIN;
				cmd.seq[0].cmd[0].file[0].file = "define.h";
			cmd.seq[0].cmd[1].cmd = "/usr/bin/tr";
			cmd.seq[0].cmd[1].argv = (char *[]){"tr", "#", "@", NULL};
			cmd.seq[0].cmd[1].file_count = 1;
			cmd.seq[0].cmd[1].file = gb_malloc(sizeof(t_file) * 1);
				cmd.seq[0].cmd[1].file[0].type = T_REDOUT;
				cmd.seq[0].cmd[1].file[0].file = "out.txt";
		cmd.seq[1].type = T_OR;
		cmd.seq[1].cmd_count = 1;
		cmd.seq[1].pipe_count = 0;
		cmd.seq[1].pid = gb_malloc(sizeof(pid_t) * 1);
		cmd.seq[1].cmd = gb_malloc(sizeof(t_cmd) * 1);
			cmd.seq[1].cmd[0].cmd = "/bin/echo";
			cmd.seq[1].cmd[0].argv = (char *[]){"echo", "fail", NULL};
			cmd.seq[1].cmd[0].file_count = 0;
			cmd.seq[1].cmd[0].file = NULL;
	# endif
	// echo hello | cat -e | tr h H || echo goodbye | cat -e | tr o e && echo wait | cat -e | tr w t
	# if TEST == 10
	cmd.seq_count = 3;
	cmd.pid = gb_malloc(sizeof(pid_t) * 3);
	cmd.seq = gb_malloc(sizeof(t_pipe) * 3);
		cmd.seq[0].type = T_PIPE;
		cmd.seq[0].cmd_count = 3;
		cmd.seq[0].pipe_count = 2;
		cmd.seq[0].pid = gb_malloc(sizeof(pid_t) * 3);
		cmd.seq[0].pipefd = gb_malloc(sizeof(int *) * 2);
			cmd.seq[0].pipefd[0] = gb_malloc(sizeof(int) * 2);
			cmd.seq[0].pipefd[1] = gb_malloc(sizeof(int) * 2);
		cmd.seq[0].cmd = gb_malloc(sizeof(t_cmd) * 3);
			cmd.seq[0].cmd[0].cmd = "/bin/echo";
			cmd.seq[0].cmd[0].argv = (char *[]){"echo", "hello", NULL};
			cmd.seq[0].cmd[0].file_count = 0;
			cmd.seq[0].cmd[0].file = NULL;
			cmd.seq[0].cmd[1].cmd = "/usr/bin/cat";
			cmd.seq[0].cmd[1].argv = (char *[]){"cat", "-e", NULL};
			cmd.seq[0].cmd[1].file_count = 0;
			cmd.seq[0].cmd[1].file = NULL;
			cmd.seq[0].cmd[2].cmd = "/usr/bin/tr";
			cmd.seq[0].cmd[2].argv = (char *[]){"tr", "h", "H", NULL};
			cmd.seq[0].cmd[2].file_count = 0;
			cmd.seq[0].cmd[2].file = NULL;
		cmd.seq[1].type = T_OR;
		cmd.seq[1].cmd_count = 3;
		cmd.seq[1].pipe_count = 2;
		cmd.seq[1].pid = gb_malloc(sizeof(pid_t) * 3);
		cmd.seq[1].pipefd = gb_malloc(sizeof(int *) * 2);
			cmd.seq[1].pipefd[0] = gb_malloc(sizeof(int) * 2);
			cmd.seq[1].pipefd[1] = gb_malloc(sizeof(int) * 2);
		cmd.seq[1].cmd = gb_malloc(sizeof(t_cmd) * 3);
			cmd.seq[1].cmd[0].cmd = "/bin/echo";
			cmd.seq[1].cmd[0].argv = (char *[]){"echo", "goodbye", NULL};
			cmd.seq[1].cmd[0].file_count = 0;
			cmd.seq[1].cmd[0].file = NULL;
			cmd.seq[1].cmd[1].cmd = "/usr/bin/cat";
			cmd.seq[1].cmd[1].argv = (char *[]){"cat", "-e", NULL};
			cmd.seq[1].cmd[1].file_count = 0;
			cmd.seq[1].cmd[1].file = NULL;
			cmd.seq[1].cmd[2].cmd = "/usr/bin/tr";
			cmd.seq[1].cmd[2].argv = (char *[]){"tr", "o", "e", NULL};
			cmd.seq[1].cmd[2].file_count = 0;
			cmd.seq[1].cmd[2].file = NULL;
		cmd.seq[2].type = T_AND;
		cmd.seq[2].cmd_count = 3;
		cmd.seq[2].pipe_count = 2;
		cmd.seq[2].pid = gb_malloc(sizeof(pid_t) * 3);
		cmd.seq[2].pipefd = gb_malloc(sizeof(int *) * 2);
			cmd.seq[2].pipefd[0] = gb_malloc(sizeof(int) * 2);
			cmd.seq[2].pipefd[1] = gb_malloc(sizeof(int) * 2);
		cmd.seq[2].cmd = gb_malloc(sizeof(t_cmd) * 3);
			cmd.seq[2].cmd[0].cmd = "/bin/echo";
			cmd.seq[2].cmd[0].argv = (char *[]){"echo", "wait", NULL};
			cmd.seq[2].cmd[0].file_count = 0;
			cmd.seq[2].cmd[0].file = NULL;
			cmd.seq[2].cmd[1].cmd = "/usr/bin/cat";
			cmd.seq[2].cmd[1].argv = (char *[]){"cat", "-e", NULL};
			cmd.seq[2].cmd[1].file_count = 0;
			cmd.seq[2].cmd[1].file = NULL;
			cmd.seq[2].cmd[2].cmd = "/usr/bin/tr";
			cmd.seq[2].cmd[2].argv = (char *[]){"tr", "w", "t", NULL};
			cmd.seq[2].cmd[2].file_count = 0;
			cmd.seq[2].cmd[2].file = NULL;
	# endif
	// cat >> out.txt < in.txt
	# if TEST == 11
	cmd.seq_count = 1;
	cmd.pid = gb_malloc(sizeof(pid_t) * 1);
	cmd.seq = gb_malloc(sizeof(t_pipe) * 1);
	cmd.seq[0].type = T_PIPE;
		cmd.seq[0].cmd_count = 1;
		cmd.seq[0].pipe_count = 0;
		cmd.seq[0].pid = gb_malloc(sizeof(pid_t) * 1);
		cmd.seq[0].cmd = gb_malloc(sizeof(t_cmd) * 1);
			cmd.seq[0].cmd[0].cmd = "/usr/bin/cat";
			cmd.seq[0].cmd[0].argv = (char *[]){"cat", NULL};
			cmd.seq[0].cmd[0].file_count = 2;
			cmd.seq[0].cmd[0].file = gb_malloc(sizeof(t_file) * 2);
				cmd.seq[0].cmd[0].file[0].type = T_APPEND;
				cmd.seq[0].cmd[0].file[0].file = "out.txt";
				cmd.seq[0].cmd[0].file[1].type = T_REDIN;
				cmd.seq[0].cmd[0].file[1].file = "in.txt";
	# endif
	// cat -e < define.h | cat -e < in.txt | cat -e > out.txt
	# if TEST == 12
	cmd.seq_count = 1;
	cmd.pid = gb_malloc(sizeof(pid_t) * 1);
	cmd.seq = gb_malloc(sizeof(t_pipe) * 1);
	cmd.seq[0].type = T_PIPE;
		cmd.seq[0].cmd_count = 3;
		cmd.seq[0].pipe_count = 2;
		cmd.seq[0].pid = gb_malloc(sizeof(pid_t) * 3);
		cmd.seq[0].pipefd = gb_malloc(sizeof(int *) * 2);
			cmd.seq[0].pipefd[0] = gb_malloc(sizeof(int) * 2);
			cmd.seq[0].pipefd[1] = gb_malloc(sizeof(int) * 2);
		cmd.seq[0].cmd = gb_malloc(sizeof(t_cmd) * 3);
			cmd.seq[0].cmd[0].cmd = "/usr/bin/cat";
			cmd.seq[0].cmd[0].argv = (char *[]){"cat", "-e", NULL};
			cmd.seq[0].cmd[0].file_count = 1;
			cmd.seq[0].cmd[0].file = gb_malloc(sizeof(t_file) * 1);
				cmd.seq[0].cmd[0].file[0].type = T_REDIN;
				cmd.seq[0].cmd[0].file[0].file = "define.h";
			cmd.seq[0].cmd[1].cmd = "/usr/bin/cat";
			cmd.seq[0].cmd[1].argv = (char *[]){"cat", "-e", NULL};
			cmd.seq[0].cmd[1].file_count = 1;
			cmd.seq[0].cmd[1].file = gb_malloc(sizeof(t_file) * 1);
				cmd.seq[0].cmd[1].file[0].type = T_REDIN;
				cmd.seq[0].cmd[1].file[0].file = "in.txt";
			cmd.seq[0].cmd[2].cmd = "/usr/bin/cat";
			cmd.seq[0].cmd[2].argv = (char *[]){"cat", "-e", NULL};
			cmd.seq[0].cmd[2].file_count = 1;
			cmd.seq[0].cmd[2].file = gb_malloc(sizeof(t_file) * 1);
				cmd.seq[0].cmd[2].file[0].type = T_REDOUT;
				cmd.seq[0].cmd[2].file[0].file = "out.txt";
	# endif
	// cat -e < define.h | cat -e > out.txt | cat -e > out.txt
	# if TEST == 13
	cmd.seq_count = 1;
	cmd.pid = gb_malloc(sizeof(pid_t) * 1);
	cmd.seq = gb_malloc(sizeof(t_pipe) * 1);
		cmd.seq[0].type = T_PIPE;
		cmd.seq[0].cmd_count = 3;
		cmd.seq[0].pipe_count = 2;
		cmd.seq[0].pid = gb_malloc(sizeof(pid_t) * 3);
		cmd.seq[0].pipefd = gb_malloc(sizeof(int *) * 2);
			cmd.seq[0].pipefd[0] = gb_malloc(sizeof(int) * 2);
			cmd.seq[0].pipefd[1] = gb_malloc(sizeof(int) * 2);
		cmd.seq[0].cmd = gb_malloc(sizeof(t_cmd) * 3);
			cmd.seq[0].cmd[0].cmd = "/usr/bin/cat";
			cmd.seq[0].cmd[0].argv = (char *[]){"cat", "-e", NULL};
			cmd.seq[0].cmd[0].file_count = 1;
			cmd.seq[0].cmd[0].file = gb_malloc(sizeof(t_file) * 1);
				cmd.seq[0].cmd[0].file[0].type = T_REDIN;
				cmd.seq[0].cmd[0].file[0].file = "define.h";
			cmd.seq[0].cmd[1].cmd = "/usr/bin/cat";
			cmd.seq[0].cmd[1].argv = (char *[]){"cat", "-e", NULL};
			cmd.seq[0].cmd[1].file_count = 1;
			cmd.seq[0].cmd[1].file = gb_malloc(sizeof(t_file) * 1);
				cmd.seq[0].cmd[1].file[0].type = T_REDOUT;
				cmd.seq[0].cmd[1].file[0].file = "out.txt";
			cmd.seq[0].cmd[2].cmd = "/usr/bin/cat";
			cmd.seq[0].cmd[2].argv = (char *[]){"cat", "-e", NULL};
			cmd.seq[0].cmd[2].file_count = 1;
			cmd.seq[0].cmd[2].file = gb_malloc(sizeof(t_file) * 1);
				cmd.seq[0].cmd[2].file[0].type = T_REDOUT;
				cmd.seq[0].cmd[2].file[0].file = "out.txt";
	# endif

	// exec(&cmd, e);
	(void)cmd;

	exec(&cmd, e);

	exit_shell((char *[]){fetch_val("?", e), NULL});

	return (0);
}
