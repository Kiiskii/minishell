#include "../minishell.h"

//TODO: check error messages

void	update_env(char *new, char *old, t_envi *env)
{
	t_envi	*pwd;
	t_envi	*old_pwd;

	//check if new and old exist?
	pwd = env;
	old_pwd = env;
	while (pwd != NULL)
	{
		if (ft_strcmp(pwd->key, "PWD") == 0)
		{
			free(pwd->value);
			pwd->value = ft_strdup(new);
		}
		pwd = pwd->next;
	}
	while (old_pwd != NULL)
	{
		if (ft_strcmp(old_pwd->key, "OLDPWD") == 0)
		{
			free(old_pwd->value);
			old_pwd->value = ft_strdup(old);
		}
		old_pwd = old_pwd->next;
	}
}

int	change_dir(char *path, t_envi *env)
{
	char	*current;
	char	*old;
	
	old = getcwd(NULL, 0);
	if (!old)
	{
		ft_putstr_fd("error getcwd\n", 2);
		return (1);
	}
	if (chdir(path) != 0)
	{
		ft_putstr_fd("lash: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2); //or perror??
		return (1);
	}
	current = getcwd(NULL, 0);
	if (!current)
	{
		return (1); //error message?
	}
	update_env(current, old, env);
	return (0);
}

int	go_home(t_envi *env)
{
	t_envi	*seeker;
	char	*current;

	current = getcwd(NULL, 0);
	if (!current)
	{
		return (1); //error message?
	}
	seeker = env;
	while (seeker != NULL)
	{
		if (ft_strcmp(seeker->key, "HOME") == 0)
			break ;
		seeker = seeker->next;
	}
	if (seeker == NULL)
	{
		ft_putstr_fd("lash: cd: HOME not set\n", 2);
		return (1);
	}
	chdir(seeker->value);
	update_env(seeker->value, current, env);
	return (0);
}

int	builtin_cd(char **array, t_envi *env)
{
	if (!array[1])
		return (go_home(env));
	else if (array[2])
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
