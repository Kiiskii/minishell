#include "../minishell.h"

//need to decide whether these return something or just exit
//if given just "exit" or "exit 6", is exit written on STDOUT?
//if written on STDERR, can just write exit\n at the start regardless of rest
//check with "exit 9999999999999999999" should exit with message
//"bash: exit: 9999999999999999999: numeric argument required" and $? = 2

void	builtin_exit(char **array)
{
	ft_putstr_fd("exit\n", 2);
	if (!array[1])
		return ;
		//set $? to 0
		//exit --> maybe just exit(0);
	else if (ft_isdigit(array[1][0])) //check what you send here, need to do a loop?
	{
		if (array[2])
		{
			ft_putstr_fd("lash: exit: too man arguments\n", 2); //check if nl necessary
			//set $? to 1
		}
		else
		{
			//set $? to ft_atoi(array[1]);
			//exit
		}
	}
	else
	{
		ft_putstr_fd("lash: exit: ", 2);
		ft_putstr_fd(array[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2); //check nl or no
		//set $? to 2
		//exit
	}
}
