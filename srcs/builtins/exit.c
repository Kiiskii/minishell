#include "../minishell.h"

//check with "exit 9999999999999999999" should exit with message
//"bash: exit: 9999999999999999999: numeric argument required" and $? = 2

int	only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **array)
{
	ft_putstr_fd("exit\n", 2);
	if (!array[1])
		exit (0);
	else if (only_digits(array[1]))
	{
		if (array[2])
		{
			ft_putstr_fd("lash: exit: too many arguments\n", 2);
			return (1);
		}
		else
			exit(ft_atoi(array[1])); //needs to be atol?? bash behaves funny
	}
	else
	{
		ft_putstr_fd("lash: exit: ", 2);
		ft_putstr_fd(array[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
}
