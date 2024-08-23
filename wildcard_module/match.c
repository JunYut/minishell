# include "wildcard.h"

t_list	*ent_match(t_wildcard *wc, char *regex)
{
	t_list	*match_lst;
	t_list	*lst;
	char	*match;

	lst = wc->dirent->files;
	if (regex[0] == '.')
		lst = wc->dirent->dot_files;
	match_lst = NULL;
	while (lst)
	{
		if (ft_strlen(lst->content) < ft_strlen(regex))
		{
			lst = lst->next;
			continue ;
		}
		match = pattern_match(lst->content, wc->token, wc->pattern);
		// DPRINTF("match: %s\n\n", match);
		if (match)
			ft_lstadd_back(&match_lst, gb_lstnew(gb_strdup(match)));
		lst = lst->next;
	}
	return (match_lst);
}

// returns the matched string or NULL if it doesn't match
char	*pattern_match(char *ent, t_token *token, char **pattern)
{
	char	*pos;
	char	*tmp;
	int		len;
	int		i;
	int		j;

	tmp = ent;
	j = 0;
	i = -1;
	while (token[++i] != T_END)
	{
		// DPRINTF("ent: [%s]\n", tmp);
		// DPRINTF("pattern: [%s]\n", pattern[j]);
		len = ft_strlen(tmp);
		pos = ft_strnstr(tmp, pattern[j], len);
		if (!pos)
			return (NULL);
		if (token[i] == T_PATTERN && pos != tmp)
			return (NULL);
		else if (token[i + 1] == T_PATTERN && pos == tmp)
			return (NULL);
		tmp = pos + ft_strlen(pattern[j]);
		if (tmp[0] == '\0')
			return (ent);
		if (pattern[j + 1])
			++j;
	}
	return (ent);
}
