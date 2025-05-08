#include "../minishell.h"

static int	is_directory(char *cmd)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) != 0)
		return (0);
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("lash: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (1);
	}
	return (0);
}

static char	*create_path(char **paths, char *cmd, t_mini *lash)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		if (tmp == NULL)
			return (fail_to_malloc(lash));
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (path == NULL)
			return (fail_to_malloc(lash));
		if (check_access(path, lash) == 0)
			return (path);
		else if (check_access(path, lash) == 1)
			return (NULL);
		free(path);
		i++;
	}
	cmd_error(cmd, lash);
	return (NULL);
}

static char	**get_env_path(char **args, t_mini *lash, t_envi *env)
{
	char	**paths;

	while (env && ft_strncmp(env->key, "PATH", 4) != 0)
		env = env->next;
	if (env == NULL)
	{
		lash->exit_code = 127;
		ft_putstr_fd("lash: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": no such file or directory\n", 2);
		return (NULL);
	}
	paths = ft_split(env->value, ':');
	if (paths == NULL)
	{
		lash->exit_code = 12;
		ft_putstr_fd("Cannot allocate memory, please exit lash\n", 2);
	}
	return (paths);
}

int	path_not_created(char **path_env, t_mini *lash)
{
	if (path_env == NULL)
	{
		lash->exit_code = 127;
		free(path_env);
		return (1);
	}
	return (0);
}

char	*get_exec_path(char **args, t_mini *lash)
{
	char	*res;
	char	**path_env;
	int		access;

	if (ft_strchr(args[0], '/'))
	{
		if (is_directory(args[0]))
		{
			lash->exit_code = 126;
			return (NULL);
		}
		access = check_access(args[0], lash);
		if (access == 0)
			return (args[0]);
		else if (access == 1)
			return (NULL);
		cmd_error(args[0], lash);
		return (NULL);
	}
	path_env = get_env_path(args, lash, lash->env);
	if (path_not_created(path_env, lash))
		return (NULL);
	res = create_path(path_env, args[0], lash);
	free_arr(path_env);
	return (res);
}
