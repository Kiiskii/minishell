#include "../minishell.h"

//TODO: check path of ./minishell before checking PATH env

char	**get_bin(char **args, t_mini *lash, t_envi *env)
{
	char	**paths;

	while (env && ft_strncmp(env->key, "PATH", 4) != 0)
		env = env->next;
	if (env == NULL)
	{
		lash->exit_code = 127;
		ft_putstr_fd("Command '", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd("' not found\n", 2);
		return (NULL);
	}
	paths = ft_split(env->value, ':');
	if (paths == NULL)
	{
		lash->exit_code = 12;
		ft_putstr_fd("Cannot allocate memory\n", 2);
	}
	return (paths);
}

void    execute_external(char **args, t_mini *lash)
{
	char    **bin;
	char    **env_array;
	char    *path; //TODO change
	pid_t     pid;

	path = malloc(30 * sizeof(char)); //TODO change
	bin = get_bin(args, lash, lash->env);
	if (bin == NULL)
		return ;
	path = find_path(bin, path, args[0]);
	free_arr(bin);
	if (!path)
		return ;
	pid = fork();
	if (pid == -1)
		printf("Forking failed\n"); //TODO remove
	if (pid == 0)
	{
		env_array = env_to_arr(lash->env);
		if (!env_array)
		{
			lash->exit_code = 12;
			ft_putstr_fd("Cannot allocate memory\n", 2);
		}
		execve(path, args, env_array); //TODO check if we should pass just NULL and getenv when executing a shell
		ft_putstr_fd("Failed to execute\n", 2);
		lash->exit_code = 1;
		free_arr(env_array);
	}
	waitpid(pid, &lash->exit_code, 0);
}

void    execute_command(char **args, t_mini *lash) //lash struct with env inside?
{
	if (ft_strcmp(args[0], "cd") == 0)
		lash->exit_code = builtin_cd(args, lash->env);
	else if (ft_strcmp(args[0], "pwd") == 0)
		lash->exit_code = builtin_pwd(args);
	else if (ft_strcmp(args[0], "export") == 0)
		lash->exit_code = builtin_export(args, lash->env);
	else if (ft_strcmp(args[0], "unset") == 0)
		lash->exit_code = builtin_unset(args, lash->env);
	else if (ft_strcmp(args[0], "env") == 0)
		lash->exit_code = builtin_env(args, lash->env);
	else if (ft_strcmp(args[0], "echo") == 0)
		lash->exit_code = builtin_echo(args);
	else if (ft_strcmp(args[0], "exit") == 0)
		lash->exit_code = builtin_exit(args);
	else
		execute_external(args, lash);
	printf("EXIT CODE: %i\n", lash->exit_code);
}
