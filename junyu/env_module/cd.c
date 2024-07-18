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
		path = find_key("HOME", e->var);
	else if (*path == '-')
		path = find_key("OLDPWD", e->var);
	printf("path: %s\n", path);
}
