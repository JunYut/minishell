# include "env.h"

// a=1
// a=
// a
char **split_var(char *str)
{
	char	**split;
	int		len_key;
	int		len_value;

	split = gb_malloc(sizeof(char *) * 2);
	split[0] = ft_strdup(str, '=');
	len_key = ft_strlen(str, '=');
	len_value = ft_strlen(str + len_key + 1, '\0');
	split[1] = ft_strdup(str + len_key + 1, '\0');
	return (split);
}

char	*ft_strdup(char *str, char delim)
{
	char	*dup;
	int		len;

	len = ft_strlen(str, delim);
	if (len == -1)
		return (NULL);
	dup = gb_malloc(len + 1);
	ft_strncpy(dup, str, len);
	return (dup);
}

void ft_strncpy(char *dst, char *src, int len)
{
	int i;

	i = -1;
	while (++i < len)
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

bool	is_delim(char c)
{
	if (c == '=')
		return (true);
	return (false);
}

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
