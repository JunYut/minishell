/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:25:49 by tjun-yu           #+#    #+#             */
/*   Updated: 2024/09/10 15:38:24 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# include <stdbool.h>
# include "libft.h"
# include <termios.h>
# include <signal.h>

# define READ_SIZE 42
# define EXPORT 1
# define VAR 2

# define NODE_LEFT 1
# define NODE_RIGHT 2

extern volatile sig_atomic_t	g_wait;

typedef enum e_token_type
{
	T_WORD,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_HEREDOC,
	T_APPEND,
	T_PIPE,
	T_L_BRACKET,
	T_R_BRACKET,
	T_OR,
	T_AND,
	T_NEWLINE,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef enum e_node_type
{
	N_PIPE,
	N_AND,
	N_OR,
	N_CMD,
	N_SUBSHELL,
}	t_node_type;

typedef enum e_io_type
{
	IO_IN,
	IO_OUT,
	IO_HEREDOC,
	IO_APPEND,
}	t_io_type;

typedef enum e_parse_err_type
{
	E_NONE,
	E_MEM,
	E_SYNTAX,
	E_EOF,
}	t_parse_err_type;

typedef enum e_err_msg
{
	ERR_MSG_CMD_NOT_FOUND,
	ERR_MSG_NO_SUCH_FILE,
	ERR_MSG_IS_DIR,
	ERR_MSG_NOT_DIR,
	ERR_MSG_PERM_DENIED,
	ERR_MSG_AMBIGUOUS,
	ERR_MSG_TOO_MANY_ARGS,
	ERR_MSG_NUMERIC_REQ
}	t_err_msg;

typedef enum e_errno
{
	ERRNO_SUCCESS,
	ERRNO_GENERAL,
	ERRNO_CANT_EXEC = 126,
	ERRNO_NOT_FOUND = 127,
	ERRNO_EXEC_255 = 255
}	t_errno;

typedef enum s_wc_type
{
	WC_WILDCARD,
	WC_PATTERN,
	WC_END
}	t_wc_type;

typedef struct s_dirent
{
	t_list	*files;
	t_list	*dot_files;
}	t_dirent;

typedef struct s_wildcard
{
	t_dirent	*dirent;
	t_wc_type	*token;
	char		**pattern;
}	t_wildcard;

typedef struct s_io_node
{
	t_io_type			type;
	int					heredoc;
	char				*value;
	char				**exp_value;
	struct s_io_node	*prev;
	struct s_io_node	*next;
}	t_io_node;

typedef struct s_node
{
	t_node_type		type;
	t_io_node		*io_list;
	char			*args;
	char			**exp_args;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_parse_err
{
	t_parse_err_type	type;
	char				*str;
}	t_parse_err;

typedef struct s_err
{
	t_errno		exit_status;
	t_err_msg	msg;
	char		*cause;
}	t_err;

typedef struct s_path
{
	t_err	err;
	char	*cmd_path;
}	t_path;

typedef struct s_var
{
	int				id;
	char			*key;
	char			*value;
	struct s_var	*next;
}	t_var;

typedef struct s_env
{
	char	**envp;
	t_var	*var;
	t_var	*exp;
	int		last_var_id;
	int		last_exp_id;
}	t_env;

typedef struct s_file
{
	t_token_type	type;
	char			*file;
}	t_file;

typedef struct s_gbc
{
	void			*addr;
	struct s_gbc	*next;
}	t_gbc;

typedef struct s_minishell
{
	char			*name;
	char			*line;
	t_token			*token_list;
	t_token			*curr_token;
	t_node			*ast;
	t_parse_err		parse_err;
	bool			token_err;
	t_env			*env;
	struct termios	term;
	int				ms_stdin;
	int				ms_stdout;
	int				exit_status;
	t_gbc			*gbc;
}	t_minishell;

#endif
