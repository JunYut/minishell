# include "wildcard.h"

// Returns an array of tokens terminated by T_END
t_token	*tokenize(char *regex)
{
	t_token	*token;
	int		i;
	int		j;

	token = gb_malloc(sizeof(t_token) * (count_token(regex) + 1));
	j = 0;
	i = -1;
	while (regex[++i])
	{
		if (regex[i] == '*')
		{
			token[j++] = T_WILDCARD;
			while (regex[i + 1] && regex[i + 1] == '*')
				++i;
		}
		else
		{
			token[j++] = T_PATTERN;
			while (regex[i + 1] && regex[i + 1] != '*')
				++i;
		}
	}
	token[j] = T_END;
	return (token);
}

int	count_token(char *regex)
{
	int	count;
	int	i;
	count = 0;
	i = -1;
	while (regex[++i])
	{
		++count;
		if (regex[i] == '*')
			while (regex[i + 1] && regex[i + 1] == '*')
				++i;
		else
			while (regex[i + 1] && regex[i + 1] != '*')
				++i;
	}
	return (count);
}
