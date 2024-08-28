# include "env.h"

char	**env_to_arr(t_var *var)
{
	char	**arr;
	t_var	*curr;
	int		size;

	size = 0;
	curr = var;
	while (curr->next)
	{
		++size;
		curr = curr->next;
	}
	arr = gb_malloc(sizeof(char *) * (size + 1));
	arr[size] = NULL;
	curr = var;
	size = -1;
	while (curr->next)
	{
		if (!curr->key || !curr->value)
			continue ;
		arr[++size] = gb_add(ft_strjoin(curr->key, "="));
		arr[size] = gb_add(ft_strjoin(arr[size], curr->value));
		curr = curr->next;
	}
	return (arr);
}

// copies until pos - 1
// "hello world", 5 -> "hello"
char	*ft_strndup(char *str, int pos)
{
	char	*dup;

	if (pos == -1)
		return (NULL);
	dup = gb_malloc(pos + 1);
	ft_strncpy(dup, str, pos);
	return (dup);
}

void ft_strncpy(char *dst, char *src, int len)
{
	int i;

	i = -1;
	while (++i < len && src[i])
		dst[i] = src[i];
	dst[i] = '\0';
}

// "hello", '\0' -> 5
// "hello", 'o' -> 4
// "hello", 'z' -> -1
int	find_pos(char *str, char delim)
{
	int i;

	i = -1;
	while (str[++i] && str[i] != delim)
		;
	if (str[i] != delim)
		return (-1);
	return (i);
}

int	is_numeric(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}
