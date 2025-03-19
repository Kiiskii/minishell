#include "../minishell.h"

//#include <unistd.h>
//#include <stdio.h>

//echo with option -n. Takes a char **array, where "echo" is in index 0
//checks if -n option is in place (also -nnnn and -n -n -n)

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
		printf("%s", array[i]);
		if (array[i + 1])
			printf(" ");
		i++;
	}
	if (nl_check == 1)
		printf("\n");
	return (0);
}

//int	main(int argc, char **argv)
//{
//	if (argc == 0)
//		return (0);
//	builtin_echo(argv + 1);
//	return (0);
//}
