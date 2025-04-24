#include "../minishell.h"

char	*check_pwd(t_envi *env)
{
	char	*path;

	while (env != NULL)
	{
		if (ft_strcmp(env->key, "PWD") == 0)
		{
			path = ft_strdup(env->value);
			if (!path)
				return (NULL);
			return (path);
		}
		env = env->next;
	}
	return (NULL);
}

int	builtin_pwd(char **array, t_envi *env)
{
	char	*pathname;
	char	*pwd_path;

	if (array[1] && array[1][0] == '-')
	{
		printf("lash: pwd: options for pwd are not supported\n");
		return (2);
	}
	pwd_path = check_pwd(env);
	if (pwd_path)
	{
		printf("%s\n", pwd_path);
		free(pwd_path);
		return (0);
	}
	pathname = getcwd(NULL, 0);
	if (!pathname)
	{
		perror("lash: getcwd\n");
		return (errno);
	}
	printf("%s\n", pathname);
	free(pathname);
	return (0);
}
