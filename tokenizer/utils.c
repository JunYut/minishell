# include "utils.h"
# include "debug.h"

// requires full path
int	is_cmd(const char *iden)
{
	if (!iden)
		return (0);
	if (access(iden, X_OK) == 0)
		return (1);
	return (0);
}

int	is_operator(t_token t)
{
	return (t == T_PIPE || t == T_REDIRECT_IN || t == T_REDIRECT_OUT
		|| t == T_APPEND || t == T_HERE_DOC || t == T_AND || t == T_OR);
}

void	free_2d(void **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
