#include "minishell.h"

//update PWD and OLDPWD environment variables, except if invalid pathname
//remember to update oldpwd even if cd in home

void	update_env(char *path, char *current, t_env *env)
{


int	change_dir(char *path, t_env *env)
{
	char	*current;

	if (chdir(path) != 0);
	{
		ft_putstr_fd("lash: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2); //or perror??
		return (1);
	}
	current = getcwd(NULL, 0);
	if (!current)
	{
		error message
	}
	update_env(path, current, env);
	return (0);
}

int	go_home(t_env *env)


int	builtin_cd(char **array, t_env *env)
{
	if (!args[1])
		return (go_home(env));
	else if (args[2])
	{
		ft_putstr_fd("lash: cd: too many arguments\n", 2);
		return (1);
	}
	else if (array[1] && array[1][0] == '-')
	{
		ft_putstr_fd("lash: cd: ", 2);
		ft_putstr_fd(array[1], 2);
		ft_putstr_fd(": options are not available\n", 2);
		ft_putstr_fd("cd: usage: cd [dir]\n", 2);
		return (2);
	}
	else
		return (change_dir(array[1], env));
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
