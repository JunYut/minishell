# include "env.h"

// Expected input:
// absolute path
// relative path
// NULL ; ~
// ~username
// . ; ..
// -
void	cd(char *path, t_env *e)
{
	if (!path || *path == '\0' || *path == '~')
		path = fetch_val("HOME", e);
	else if (ft_strcmp(path, "-") == 0)
		path = fetch_val("OLDPWD", e);
	else if (ft_strcmp("..", path) == 0)
		path = parent_dir(fetch_val("PWD", e));
	if (ft_strcmp(path, "-") == 0)
	{
		printf("cd: OLDPWD not set\n");
		return ;
	}
	if (!fetch_val("OLDPWD", e))
		add_var(e, "OLDPWD", fetch_val("PWD", e));
	set_val(e, "OLDPWD", fetch_val("PWD", e));
	set_val(e, "PWD", path);
	chdir(path);
}

char	*parent_dir(char *pwd)
{
	int	i;

	i = ft_strlen(pwd, '\0');
	while (--i > 0 && pwd[i] != '/')
		;
	return (ft_strdup(pwd, i));
}
