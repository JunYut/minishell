/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:57:24 by tjun-yu           #+#    #+#             */
/*   Updated: 2024/09/02 10:48:51 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <errno.h>
# include <stdio.h>
# include "define.h"
# include "libft.h"

int	print_builtin_err(char *builtin, char *cause, char *error);
int	print_err(char *cause, char *error);

# endif
