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
		path = fetch_val("HOME", e->var);
	else if (ft_strcmp(path, "-") == 0)
		path = fetch_val("OLDPWD", e->var);
	else if (ft_strcmp("..", path) == 0)
		path = parent_dir(fetch_val("PWD", e->var));
	printf("path: %s\n", path);
	chdir(path);
	char	buf[1024];
	printf("cwd: %s\n", getcwd(buf, sizeof(buf)));
}

char	*parent_dir(char *pwd)
{
	int	i;

	printf("pwd: %s\n", pwd);
	i = ft_strlen(pwd, '\0');
	while (--i > 0 && pwd[i] != '/')
		;
	return (ft_strdup(pwd, i));
}
