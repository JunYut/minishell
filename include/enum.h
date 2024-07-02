# pragma once

typedef enum e_token
{
	T_CMD,
	T_ARG,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_HERE_DOC,
	T_APPEND,
	T_PIPE,
	T_L_PAREN,
	T_R_PAREN,
	T_SUBSHELL,
	T_OR,
	T_AND,
	T_NEWLINE,
	T_INVALID = -1
}	t_token;
