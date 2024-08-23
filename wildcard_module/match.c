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
		DPRINTF("match: %s\n", match);
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
	int		len;
	int		i;

	i = -1;
	while (token[++i] != T_END)
	{
		DPRINTF("ent: %s\n", ent);
		DPRINTF("pattern: %s\n", pattern[i]);
		len = ft_strlen(ent);
		pos = ft_strnstr(ent, pattern[i], len);
		if (!pos)
			return (NULL);
		if (token[i] == T_PATTERN && pos != ent)
			return (NULL);
		else if (token[i + 1] == T_PATTERN && pos == ent)
			return (NULL);
		ent = pos + ft_strlen(pattern[i]);
	}
	return (ent);
}
