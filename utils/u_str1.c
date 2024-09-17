/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_str1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 13:20:12 by we                #+#    #+#             */
/*   Updated: 2024/09/17 10:26:01 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	**insert_string_array(char **dest, char **src, int insert_index)
{
	char	**inserted;
	int		dest_size;

	dest_size = count_strings(dest);
	if (insert_index < 0 || insert_index > dest_size)
	{
		printf("Invalid insertion index.\n");
		return (NULL);
	}
	inserted = insert(dest, src, insert_index);
	if (inserted == NULL)
	{
		printf("Failed to insert string array.\n");
		return (NULL);
	}
	// free(dest);
	return (inserted);
}

char	**insert(char **dest, char **src, int insert_index)
{
	char	**new_dest;
	int		dest_size;
	int		src_size;
	int		i;

	dest_size = count_strings(dest);
	src_size = count_strings(src);
	new_dest = gbc_malloc((dest_size + src_size + 1) * sizeof(char *));
	if (new_dest == NULL)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < insert_index)
		new_dest[i] = (dest)[i];
	i = -1;
	while (++i < src_size)
		new_dest[insert_index + i] = src[i];
	i = insert_index - 1;
	while (++i < dest_size)
		new_dest[src_size + i] = (dest)[i + 1];
	new_dest[dest_size + src_size] = NULL;
	return (new_dest);
}

int	count_strings(char **array)
{
	int	count;

	count = 0;
	if (!array || !array[0])
		return (0);
	while (array[count] != NULL)
		count++;
	return (count);
}
