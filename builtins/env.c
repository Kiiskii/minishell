#include "minishell.h"

//takes a char **array where "env" is at index 0 and head node to env list

void	builtin_env(char **array, t_env *env)
{
	int	index;
	t_env	*trav;

	if (array[1])
	{
		printf("Error\nOptions and arguments for env are not supported.\n");
		exit(1); //need to decide error and exit structure
	}
	index = 0;
	trav = env;
	while (trav != NULL)
	{
		printf("%s\n", trav->value);
		trav = trav->next;
	}
}
