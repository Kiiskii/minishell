#include "../minishell.h"

static int	check_option(char **array)
{
	if (array[1][0] == '-' && array[1][1])
	{
		ft_putstr_fd("lash: export: ", 2);
		ft_putstr_fd(array[1], 2);
		ft_putstr_fd(": options not supported\n", 2);
		ft_putstr_fd("export: usage: export [name[=value ...]\n", 2);
		return (1);
	}
	return (0);
}

void	builtin_export(char **array, t_envi *env, t_mini *lash)
{
	int		i;
	int		exit_code;

	i = 1;
	exit_code = 0;
	if (!array[i])
	{
		lash->exit_code = (print_alphabetised(env));
		return ;
	}
	while (array[i])
	{
		if (i == 1 && check_option(array) == 1)
		{
			lash->exit_code = 2;
			return ;
		}
		else
			exit_code = modify_env(array[i], env);
		if (exit_code == 1)
			lash->exit_code = 1;
		i++;
	}
	if (lash->exit_code != 1)
		lash->exit_code = 0;
}
