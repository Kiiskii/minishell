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

void	modify_existing(char *str, t_env *env)
{
	
}

_Bool	check_existing(char *str, t_env *env)
{
	t_env	*trav;

	trav = env;
	while (trav != NULL)
	{
		if (trav->key == str)
			return (1);
		trav = trav->next;
	}
	return (0);
}

int	builtin_export(char **array, t_env *env)
{
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
			printf("\"%s=%s\n\"", alphalist->key, alphalist->value);
			alphalist = alphalist->next;
			trav = trav->next;
		}
		return (0); //return success
	}
	else
	{
		while (array[i])
		{
			exit_code = is_valid_input(array[i]);
			if (array[1][0] == '-' && array[1][1])
			{
				ft_putstr_fd("lash: export: ", 2);
				ft_putstr_fd(array[1], 2);
				ft_putstr_fd("Options not supported\n", 2);
				ft_putstr_fd("export: usage: export [name[=value ...]\n", 2);
				return (2);
			}
			else if (is_valid_input(array[i]) == 0)
			{
				ft_putstr_fd("lash: export: '", 2);
				ft_putstr_fd(array[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				exit_code = 1;
			}
			else if (check_existing(array[i], env) == 1)
				modify_existing(array[i], env);
			else
				add_new(array[i], env);
			i++;
		}
	}

	//check if env var already exists, in which case replace
	//create new node for env

	//if you say WORD= then value is an empty string ""
	//with "export -" -->bash: export: `-': not a valid identifier -->exit code 1 BUT FOLLOWING KEYS
	//ADDED TO LIST
	//with "export -m" bash: export: -m: invalid option\n
	//export: usage: export [-fn] [name[=value]...] or export -p err -->exit_code 2 AND FOLLOWING
	//KEY NOT ADDED TO LIST
	//if error in middle, eg. "export THIS=this -m/- HELLO=WORD" -->"bash: export: `-m': not a valid identifier"
	//and exit code 1 BUT valid keys get added to list
}
