#include "../minishell.h"

int	protected_env(char *str)
{
	if (str[0] == '_' && str[1] == '\0')
		return (1);
	return (0);
}

void	remove_env(char	*str, t_envi **env)
{
	t_envi	*trav;
	t_envi	*prev;

	trav = *env;
	prev = NULL;
	if (protected_env(str))
		return ;
	while (trav != NULL)
	{
		if (ft_strcmp(trav->key, str) == 0)
		{
			if (prev == NULL)
				*env = trav->next;
			else
				prev->next = trav->next;
			free(trav->key);
			free(trav->value);
			free(trav);
			return ;
		}
		prev = trav;
		trav = trav->next;
	}
}

int	builtin_unset(char **array, t_envi *env)
{
	int	 i;

	i = 1;
	if (!array[1])
		return (0);
	else if (array[1][0] == '-' && array[1][1])
	{	
		ft_putstr_fd("lash: unset: ", 2);
		ft_putstr_fd(array[1], 2);
		ft_putstr_fd(": options not supported\n", 2);
		ft_putstr_fd("unset: usage: unset [name ...]\n", 2);
		return (2);
	}
	while (array[i])
	{
		remove_env(array[i], &env);
		i++;
	}
	return (0);
}
