# include "wildcard.h"

// Returns an array of tokens terminated by T_END
t_token	*tokenize(char *str)
{
	t_token	*token;
	int		i;
	int		j;

	token = gb_malloc(sizeof(t_token) * (count_token(str) + 1));
	j = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '*')
		{
			token[j++] = T_WILDCARD;
			while (str[i + 1] && str[i + 1] == '*')
				++i;
		}
		else
		{
			token[j++] = T_PATTERN;
			while (str[i + 1] && str[i + 1] != '*')
				++i;
		}
	}
	token[j] = T_END;
	return (token);
}

int	count_token(char *str)
{
	int	count;
	int	i;
	count = 0;
	i = -1;
	while (str[++i])
	{
		++count;
		if (str[i] == '*')
			while (str[i + 1] && str[i + 1] == '*')
				++i;
		else
			while (str[i + 1] && str[i + 1] != '*')
				++i;
	}
	return (count);
}
