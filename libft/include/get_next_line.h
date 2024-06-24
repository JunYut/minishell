/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:10:27 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/02/04 20:24:25 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# ifndef OPEN_MAX
#  define OPEN_MAX 4096
# endif

char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_has_newline(char *s);
char	*ft_store_str(int fd, char *stored);
char	*ft_get_line(char *stored);
char	*ft_get_new_stored(char *stored);
char	*get_next_line(int fd);

#endif
