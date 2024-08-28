# include "env.h"

// Expected input:
// absolute path [x]
// relative path [x]
// NULL ; ~		 [x]
// ~username
// . ; ..		 [x]
// -			 [x]
void	cd(char **path, t_env *e)
{
	char	*target;

	if (count_args(path, "cd", e) > 1)
		return ;
	target = *path;
	if (!*path || **path == '\0' || **path == '~')
		target = fetch_val("HOME", e);
	else if (ft_strcmp(*path, "-") == 0)
		target = fetch_val("OLDPWD", e);
	if (ft_strcmp(*path, "-") == 0 && !target)
	{
		printf("minishell: cd: OLDPWD not set\n");
		set_val(e, "?", "1");
		return ;
	}
	else if (ft_strcmp(*path, "-") == 0 && target)
		printf("%s\n", target);
	if (*path && **path == '~' && *(*path + 1) != '\0')
		target = ft_strjoin("/home/", *path + 1);
	if (!fetch_val("OLDPWD", e))
		add_ent(e, "OLDPWD", fetch_val("PWD", e));
	if (chdir(target) == -1)
	{
		perror("minishell: cd");
		set_val(e, "?", "1");
	}
	else
		set_val(e, "OLDPWD", fetch_val("PWD", e));
	set_val(e, "PWD", gb_add(getcwd(NULL, 0)));
}

int	count_args(char **path, char *func, t_env *e)
{
	int	i;

	if (!path)
		return (0);
	i = 0;
	while (path[i])
		i++;
	if (i > 1)
	{
		printf("minishell: %s: too many arguments\n", func);
		set_val(e, "?", "1");
	}
	return (i);
}
