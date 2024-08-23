# include "env.h"

// Expected input:
// absolute path [x]
// relative path [x]
// NULL ; ~		 [x]
// ~username
// . ; ..		 [x]
// -			 [x]
void	cd(char *path, t_env *e)
{
	char	*target;

	target = path;
	if (!path || *path == '\0' || *path == '~')
		target = fetch_val("HOME", e);
	else if (ft_strcmp(path, "-") == 0)
		target = fetch_val("OLDPWD", e);
	if (ft_strcmp(path, "-") == 0 && !target)
	{
		printf("cd: OLDPWD not set\n");
		return ;
	}
	else if (ft_strcmp(path, "-") == 0 && target)
		printf("%s\n", target);
	if (path && *path == '~' && *(path + 1) != '\0')
		target = ft_strjoin("/home/", path + 1);
	if (!fetch_val("OLDPWD", e))
		add_ent(e, "OLDPWD", fetch_val("PWD", e));
	if (chdir(target) == -1)
		perror("minishell: cd");
	else
		set_val(e, "OLDPWD", fetch_val("PWD", e));
	set_val(e, "PWD", gb_add(getcwd(NULL, 0)));
}
