#include "minishell.h"

//takes a char **array where "env" is at index 0 and head node to env list

int	builtin_env(char **array, t_env *env)
{
	t_env	*trav;

	if (array[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd("options and arguments for env are not supported\n", 2);
		return (ERROR_CODE); //return 125 or 127 depending on error
	}
	trav = env;
	while (trav != NULL)
	{
		if (trav->value != NULL)
		{
			printf("%s", trav->key);
			printf("=");
			printf("%s\n", trav->value);
		}
		trav = trav->next;
	}
	return (0);
}
