#include "../minishell.h"

//bash exit returns 125 on invalid option and 
//127 on "No such file or directory" (when second
//argument does not begin with '-'.

int	builtin_env(char **array, t_envi *env)
{
	t_envi	*trav;

	if (array[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd("options and arguments for env are not supported\n", 2);
		return (125);
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
