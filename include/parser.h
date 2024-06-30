/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:34:11 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/06/30 22:17:17 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "libft.h"
#include "tokenizer.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

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

typedef	struct s_io_node
{
	t_io_type	type;
	char	*value;
	char	**expanded_value;
	int		here_doc;
	struct s_io_node	*prev;
	struct s_io_node	*next;
}	t_io_node;


typedef struct s_node
{
	t_node_type	type;
	t_io_node	*io_list;
	char		*args;
	char		**expanded_args;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

#endif
