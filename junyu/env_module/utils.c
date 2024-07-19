# include "env.h"

// a=1 : export: a="1"; var: a=1
// a= : export: a=""; var: a=
// a : export: a; var: [nothing]
char **split_var(char *str)
{
	char	**split;

	if (str == NULL)
		return (NULL);
	split = gb_malloc(sizeof(char *) * 2);
	split[0] = ft_strdup(str, ft_strlen(str, '='));
	if (split[0] == NULL)
	{
		split[0] = ft_strdup(str, ft_strlen(str, '='));
		split[1] = NULL;
		return (split);
	}
	split[1] = ft_strdup(str + ft_strlen(str, '=') + 1, ft_strlen(str, '\0'));
	return (split);
}

// copies until pos - 1
// "hello world", 5 -> "hello"
char	*ft_strdup(char *str, int pos)
{
	char	*dup;

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

int ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (false);
	i = -1;
	while ((s1[++i] && s2[i]) && (s1[i] == s2[i]))
		;
	return (s1[i] - s2[i]);
}


// "hello", '\0' -> 5
// "hello", 'o' -> 4
// "hello", 'z' -> -1
int	ft_strlen(char *str, char delim)
{
	int i;

	i = -1;
	while (str[++i] && str[i] != delim)
		;
	if (str[i] != delim)
		return (-1);
	return (i);
}
