#include "../minishell.h"

int	check_nl(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(char **array)
{
	int	i;
	int	nl_check;

	i = 1;
	nl_check = 1;
	while (array[i])
	{
		if (check_nl(array[i]) == 0)
			break ;
		nl_check = 0;
		i++;
	}
	while (array[i])
	{
		write(1, array[i], ft_strlen(array[i]));
		if (array[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (nl_check == 1)
		write(1, "\n", 1);
	return (0);
}
