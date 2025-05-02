#include "../minishell.h"

int	builtin_pwd(char **array, t_envi *env)
{
	char	*pathname;

	if (array[1] && array[1][0] == '-')
	{
		printf("lash: pwd: options for pwd are not supported\n");
		return (2);
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
