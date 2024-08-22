/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:21:59 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/21 12:47:25 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define READ_SIZE 42
# define ERRNO_SUCCESS 0
# define ERRNO_FAIL 1

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
	ERR_MSG_PERM_DENIED,
	ERR_MSG_AMBIGUOUS,
	ERR_MSG_TOO_MANY_ARGS,
	ERR_MSG_NUMERIC_REQUI
}	t_err_msg;

typedef enum e_errno
{
	ERR_NO_SUCCESS,
	ERR_NO_GENERAL,
	ERR_NO_CANT_EXEC = 126,
	ERR_NO_NOT_FOUND,
	ERR_NO_EXEC_255 = 255
}	t_errno;


typedef	struct s_io_node
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
	t_errno		errno;
	t_err_msg	err_msg;
	char	*cause;
} t_err;

typedef struct s_path
{
	t_err	err;
	char	*path;
} t_path;

typedef struct s_minishell
{
	t_token		*token_list;
	t_token		*curr_token;
	t_node		*ast;
	t_parse_err	parse_err;
	bool		token_err;
	int			exit_status;
	char		*line;
	t_gbc		*gbc;
	char		**envp;
}	t_minishell;

# define EXPORT 1
# define VAR 2

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

#endif
