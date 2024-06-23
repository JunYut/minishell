/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:52:22 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/06/23 15:22:25 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	main(void)
{
	while (1)
	{
		char	*str;

		str = readline("minishell> ");
		if (str == NULL)
			break ;
		add_history(str);
	}
	return (0);
}
