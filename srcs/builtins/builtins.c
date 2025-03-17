#include <stdio.h>
#include <unistd.h>

void	builtin_exit(array)
{
	// return an int that is the exit value
	// or just exit??

	if (!array[1])
		//set $? to 0 and exit --> maybe just exit(0);
	else if (is_numeric(array[1]))
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

void	builtin_export(array, t_env *env)
{
	//usage: export VAR_NAME="Hello" or export VAR_1="first" VAR_2="second" WORKS WITHOUT QUOTES and
	//with single quotes
	//in case of VAR_NAME= adds VAR_NAME= to env list
	//!!if no arguments given, just prints exported variables in alphabetical order with "declare -x" in front

	//when adding a variable to the environment array, first check if the array is full
	//e.g. env->len + 1 >= env->capacity

	if (!array[1])
	{
		//alphabetise env list (ft_strcmp? make new linked list in which nodes are in order?);
		while (list exists)
			printf("declare -x");
			print alphlist->value[i]
			alphlist = alphlist->next;
			i++;
		return ; //return success
	}
	//check if array[1] is valid input


	//something like env->envp[env->len] = tmp;


int		check_nl(char *str)
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

void	builtin_echo(array)
{
	int	i;
	int	nl_check;

	i = 1; //or 0 depending whether the array contains 'echo' or just its arguments?
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
			write(1, " ", 1);
		i++;
	}
	if (nl_check == 1)
		write(1, "\n", 1);
}

void	builtin_cd(char **array, t_env *env)
{
	if (array[1] != a valid path) //or 0 depending on contents of array
	{
		printf("Provide a valid path for command cd");
		error_and_exit;
	}
	chdir(arr[1]);
	//error check this
}



//int	builtin_cd(void)
//{
//	char	*pwd;

//	pwd = getcwd(NULL, 0);
//    printf("pwd before chdir: %s\n", pwd);
//	chdir("/home/lguillen/minishell_github/execution");
//	pwd = getcwd(NULL, 0);
//    printf("pwd after chdir: %s\n", pwd);
//	return (0);
//}

//int	main(void)
//{
//	builtin_cd();
//	return (0);
//}

int	builtin_pwd(some array)
{
	char	*pathname;

	if (after pwd there is "-") //check the element in the array following pwd, it should be NULL 
	{
		printf("Options for pwd are not supported.");
		error_and_exit();
	}
	pathname = getcwd(NULL, 0);
	if (!pathname)
	{
		printf("Error getcwd");
		return (1);
	}
	printf("%s\n", pathname);
	free(pathname); //As an extension to the POSIX.1-2001 standard, glibc's getcwd()
       //allocates the buffer dynamically using malloc(3) if buf is NULL.
       //In this case, the allocated buffer has the length size unless size
       //is zero, when buf is allocated as big as necessary.  The caller
       //should free(3) the returned buffer.
	return (0);
}

//int	test_pwd(void)
//{
//	char	*name;
//
//	name = getcwd(NULL, 0);
//	printf("%s\n", name);
//	return (0);
//}
//
//int	main(void)
//{
//	test_pwd();
//	return (0);
//}

void	builtin_env(char **array, t_env *env) //or whatever struct we use to initialise the char **env)
{
	int	index;

	if (array[1])
	{
		printf("Error\nOptions and arguments for env are not supported.\n");
		exit(1); //need to decide error and exit structure
	}
	index = 0;
	while (index < env->len)
	{
		printf("%s\n", env->envp[index]);
		i++;
	}
