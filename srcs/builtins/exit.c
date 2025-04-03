#include "../minishell.h"

//check with "exit 9999999999999999999" should exit with message
//"bash: exit: 9999999999999999999: numeric argument required" and $? = 2
//to do: negative values
//to do: exit + |

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

int	builtin_exit(char **array) //need to send a struct around that carries ret_value
{
	ft_putstr_fd("exit\n", 2);
	if (!array[1])
		exit(0); //is it ever something different? Need to be last->exit_code?
	else if (only_digits(array[1])) //to do: also + and - and then only numbers
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
