#include "../minishell.h"

char	*create_path(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		if (tmp == NULL)
			ft_putstr_fd("Cannot allocate memory, please exit lash\n", 2);
		path = ft_strjoin(tmp, cmd);
		if (path == NULL)
			ft_putstr_fd("Cannot allocate memory, please exit lash\n", 2);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*get_path(char **args, t_mini *lash)
{
	char	*res;
	char	**path_env;

	if (access(args[0], X_OK) == 0)
		return (args[0]);
	path_env = get_env_path(args, lash, lash->env);
	if (path_env == NULL)
	{
		lash->exit_code = 12;
		free(path_env);
		return (NULL);
	}
	res = create_path(path_env, args[0]);
	free(path_env);
	return (res);
}

void	exec_ext_child(t_mini *lash, char *path, char **args)
{
	char	**env_array;

	env_array = env_to_arr(lash->env);
	if (!env_array)
		ft_putstr_fd("Cannot allocate memory, please exit lash\n", 2);
	execve(path, args, env_array);
	ft_putstr_fd("Failed to execute\n", 2);
	lash->exit_code = 127;
	if (errno == EACCES)
		lash->exit_code = 126;
	free_arr(env_array);
}

void	execute_external(char **args, t_mini *lash)
{
	char	*path;
	pid_t	pid;

	path = get_path(args, lash);
	if (!path)
	{
		ft_putstr_fd("Command '", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd("' not found\n", 2);
		lash->exit_code = 127;
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("lash: fork");
		lash->exit_code = errno;
		return ;
	}
	if (pid == 0)
		exec_ext_child(lash, path, args);
	waitpid(pid, &lash->exit_code, 0);
	free(path);
}
