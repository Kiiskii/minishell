#include "minishell.h"

int	builtin_unset(char **array, t_env *env)
{
	int	 i;

	i = 1;
	if (!array[1])
		return (0);
	else if (array[1][0] == '-' && array[1][1])
	{	
		ft_putstr("lash: unset: ", 2);
		ft_putstr(array[1], 2);
		ft_putstr(": options not supported\n", 2);
		ft_putstr("unset: usage: unset [name ...]\n");
		return (2);
	}
	while (array[i])
	{
		if (input_is_valid(array[i])


}
	
