# include "env.h"

char **split_env(char *str, t_gbc *gbc)
{
	char	**split;
	int		len_key;
	int		len_value;

	len_key = ft_strlen(str, '=');
	len_value = ft_strlen(str + len_key + 1, '\0');
	split = gb_malloc(gbc, sizeof(char *) * 2);
	split[0] = gb_malloc(gbc, len_key + 1);
	split[1] = gb_malloc(gbc, len_value + 1);
	ft_strncpy(split[0], str, len_key);
	ft_strncpy(split[1], str + len_key + 1, len_value);
	return (split);
}

void ft_strncpy(char *dst, char *src, int len)
{
	int i;

	i = -1;
	while (++i < len)
		dst[i] = src[i];
	dst[i] = '\0';
}

bool ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (false);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	if (*s1 || *s2)
		return (false);
	return (true);
}

bool	is_key(char c)
{
	if (c == '=')
		return (true);
	return (false);
}

int	ft_strlen(char *str, char c)
{
	int i;

	i = -1;
	while (str[++i] && str[i] != c)
		;
	return (i);
}
