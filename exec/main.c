# include "exec.h"
# include "signal.h"
# include "gbc.h"
# include "define.h"

void	print_int(void *data);

# define TEST 3

int main(int ac, char **av, char **envp)
{
	t_env	*e = dup_env(envp);
	t_cmd_line	cmd;

	// clear
	# if TEST == 0
	cmd.redirs = gb_malloc(1 * sizeof(t_redir));
		cmd.redirs[0].type = T_END;
		cmd.redirs[0].file = NULL;
	cmd.cmds = gb_malloc(2 * sizeof(t_cmd));
		cmd.cmds[0].type = T_CMD;
		cmd.cmds[0].cmd = "/usr/bin/clear";
		cmd.cmds[0].argv = gb_malloc(2 * sizeof(char *));
			cmd.cmds[0].argv[0] = "clear";
			cmd.cmds[0].argv[1] = NULL;
		cmd.cmds[1].type = T_END;
		cmd.cmds[1].cmd = NULL;
		cmd.cmds[1].argv = NULL;
	# endif
	// cat -en < in.txt
	# if TEST == 1
	cmd.redirs = gb_malloc(2 * sizeof(t_redir));
		cmd.redirs[0].type = T_REDIN;
		cmd.redirs[0].file = "in.txt";
		cmd.redirs[1].type = T_END;
		cmd.redirs[1].file = NULL;
	cmd.cmds = gb_malloc(2 * sizeof(t_cmd));
		cmd.cmds[0].type = T_CMD;
		cmd.cmds[0].cmd = "/usr/bin/cat";
		cmd.cmds[0].argv = gb_malloc(3 * sizeof(char *));
			cmd.cmds[0].argv[0] = "cat";
			cmd.cmds[0].argv[1] = "-en";
			cmd.cmds[0].argv[2] = NULL;
		cmd.cmds[1].type = T_END;
	# endif
	// cat -en << EOF
	# if TEST == 2
	cmd.redirs = gb_malloc(2 * sizeof(t_redir));
		cmd.redirs[0].type = T_HERE_DOC;
		cmd.redirs[0].file = "EOF";
		cmd.redirs[1].type = T_END;
		cmd.redirs[1].file = NULL;
	cmd.cmds = gb_malloc(2 * sizeof(t_cmd));
		cmd.cmds[0].type = T_CMD;
		cmd.cmds[0].cmd = "/usr/bin/cat";
		cmd.cmds[0].argv = gb_malloc(3 * sizeof(char *));
			cmd.cmds[0].argv[0] = "cat";
			cmd.cmds[0].argv[1] = "-en";
			cmd.cmds[0].argv[2] = NULL;
		cmd.cmds[1].type = T_END;
	# endif
	// cat -en in.txt > out.txt
	# if TEST == 3
	cmd.redirs = gb_malloc(2 * sizeof(t_redir));
		cmd.redirs[0].type = T_REDOUT;
		cmd.redirs[0].file = "out.txt";
		cmd.redirs[1].type = T_END;
		cmd.redirs[1].file = NULL;
	cmd.cmds = gb_malloc(2 * sizeof(t_cmd));
		cmd.cmds[0].type = T_REDOUT;
		cmd.cmds[0].cmd = "/usr/bin/cat";
		cmd.cmds[0].argv = gb_malloc(4 * sizeof(char *));
			cmd.cmds[0].argv[0] = "cat";
			cmd.cmds[0].argv[1] = "-en";
			cmd.cmds[0].argv[2] = "in.txt";
			cmd.cmds[0].argv[3] = NULL;
		cmd.cmds[1].type = T_END;
	# endif
	// env | grep PWD
	# if TEST == 4
	cmd.redirs = gb_malloc(2 * sizeof(t_redir));
		cmd.redirs[0].type = T_PIPE;
		cmd.redirs[0].file = NULL;
		cmd.redirs[1].type = T_END;
		cmd.redirs[1].file = NULL;
	cmd.cmds = gb_malloc(3 * sizeof(t_cmd));
		cmd.cmds[0].type = T_PIPE;
		cmd.cmds[0].cmd = "/usr/bin/env";
		cmd.cmds[0].argv = gb_malloc(2 * sizeof(char *));
			cmd.cmds[0].argv[0] = "env";
			cmd.cmds[0].argv[1] = NULL;
		cmd.cmds[1].type = T_CMD;
		cmd.cmds[1].cmd = "/usr/bin/grep";
		cmd.cmds[1].argv = gb_malloc(3 * sizeof(char *));
			cmd.cmds[1].argv[0] = "grep";
			cmd.cmds[1].argv[1] = "PWD";
			cmd.cmds[1].argv[2] = NULL;
		cmd.cmds[2].type = T_END;
	# endif
	// t_list
	# if TEST == 10
	(void)e;	(void)cmd; (void)envp;
	t_list	*lst = NULL;
	int		*data;

	data = gb_malloc(sizeof(int) * 4);
	data[0] = 1; 	data[1] = 2;	data[2] = 3;	data[3] = 4;
	ft_lstadd_back(&lst, ft_lstnew(data));
	data = gb_malloc(sizeof(int) * 4);
	data[0] = 5; 	data[1] = 6;	data[2] = 7;	data[3] = 8;
	ft_lstadd_back(&lst, ft_lstnew(data));

	ft_lstiter(lst, print_int);
	# endif
	// cat -e << EOF | grep lol -v > out.txt
	# if TEST == -1
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
		cmd.cmds[0].type = T_CMD;
		cmd.cmds[0].cmd = "/usr/bin/cat";
		cmd.cmds[0].argv = gb_malloc(3 * sizeof(char *));
			cmd.cmds[0].argv[0] = "cat";
			cmd.cmds[0].argv[1] = "-e";
			cmd.cmds[0].argv[2] = NULL;
		cmd.cmds[1].type = T_PIPE;
		cmd.cmds[1].cmd = "/usr/bin/grep";
		cmd.cmds[1].argv = gb_malloc(4 * sizeof(char *));
			cmd.cmds[1].argv[0] = "grep";
			cmd.cmds[1].argv[1] = "lol";
			cmd.cmds[1].argv[2] = "-v";
			cmd.cmds[1].argv[3] = NULL;
		cmd.cmds[2].type = T_END;
		cmd.cmds[2].cmd = NULL;
		cmd.cmds[2].argv = NULL;
	# endif
	// ls || echo hello world && cat define.h
	# if TEST == -1
	cmd.redirs = gb_malloc(3 * sizeof(t_redir));
		cmd.redirs[0].type = T_OR;
		cmd.redirs[0].file = NULL;
		cmd.redirs[1].type = T_AND;
		cmd.redirs[1].file = NULL;
		cmd.redirs[2].type = T_END;
		cmd.redirs[2].file = NULL;
	cmd.cmds = gb_malloc(4 * sizeof(t_cmd));
		cmd.cmds[0].type = T_CMD;
		cmd.cmds[0].cmd = "/usr/bin/ls";
		cmd.cmds[0].argv = gb_malloc(3 * sizeof(char *));
			cmd.cmds[0].argv[0] = "ls";
			cmd.cmds[0].argv[1] = NULL;
			cmd.cmds[0].argv[2] = NULL;
		cmd.cmds[1].type = T_OR;
		cmd.cmds[1].cmd = "/usr/bin/echo";
		cmd.cmds[1].argv = gb_malloc(3 * sizeof(char *));
			cmd.cmds[1].argv[0] = "echo";
			cmd.cmds[1].argv[1] = "hello world";
			cmd.cmds[1].argv[2] = NULL;
		cmd.cmds[2].type = T_AND;
		cmd.cmds[2].cmd = "/usr/bin/cat";
		cmd.cmds[2].argv = gb_malloc(3 * sizeof(char *));
			cmd.cmds[2].argv[0] = "cat";
			cmd.cmds[2].argv[1] = "define.h";
			cmd.cmds[2].argv[2] = NULL;
		cmd.cmds[3].type = T_END;
		cmd.cmds[3].cmd = NULL;
		cmd.cmds[3].argv = NULL;
	# endif

	cmd_exec(&cmd, e);

	gb_clear();

	(void)ac;
	(void)av;
	(void)e;

	return (0);
}

void	print_int(void *data)
{
	int	*ptr;

	ptr = (int *)data;
	printf("%d %d %d %d\n", ptr[0], ptr[1], ptr[2], ptr[3]);
}
