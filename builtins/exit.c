#include "minishell.h"

//need to decide whether these return something or just exit
//if given just "exit" or "exit 6", is exit written on STDOUT?
//if written on STDERR, can just write exit\n at the start regardless of rest

void	builtin_exit(array)
{
	if (!array[1])
		//set $? to 0 and exit --> maybe just exit(0);
	else if (ft_isdigit(array[1]))
	{
		if (array[2])
		{
			ft_putstr_fd("exit\n", STDERR);
			ft_putstr_fd("lash: exit: too man arguments\n", STDERR); //check if nl necessary
			//set $? to 1
		}
		else
		{
			ft_putstr_fd("exit\n", STDOUT);
			//set $? to ft_atoi(array[1]); and exit
		}
	}
	else
	{
		ft_putstr_fd("exit\nlash: exit: ", STDERR);
		ft_putstr_fd(array[1], STDERR);
		ft_putstr_fd(": numeric argument required\n", STDERR); //check nl or no
		//set $? to 2 and exit
	}
}
