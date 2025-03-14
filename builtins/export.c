#include "minishell.h"

t_env	*find_next(t_env *env)
{
	t_env	*min;
	t_env	*trav;

	trav = env;
	min = trav;
	while (trav->next != NULL)
	{
		if (ft_strcmp(trav->key, trav->next->key) < 0)
			min = trav->next;
		trav = trav->next;
	}
	return (min);
}

int	builtin_export(char **array, t_env *env)
{
	//usage: export VAR_NAME="Hello" or export VAR_1="first" VAR_2="second" WORKS WITHOUT QUOTES and
	//with single quotes
	//in case of VAR_NAME= adds VAR_NAME= to env list

	t_env	*alphalist;
	t_env	*trav;
	int		i;

	trav = env;
	i = 1;
	if (!array[i])
	{
		while (env != NULL)
		{
			printf("declare -x ");
			alphalist = find_next(env);
			printf("%s=%s\n", alphalist->key, alphalist->value);
			alphalist = alphalist->next;
			trav = trav->next;
		}
		return (0); //return success
	}
	//check if array[1] is valid input
	if (ft_strchr(array[i]) == NULL)
		return (0);
	else
	{
		while (array[i])
		{
			if (check_existing(array[i]) == 1)
				modify_existing(array[i], env);
			else
				add_new(array[i], env);
		}
	//check if env var already exists, in which case replace
	//create new node for env

	//something like env->envp[env->len] = tmp;
	
}
