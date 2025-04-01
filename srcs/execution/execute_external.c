#include "../minishell.h"

void    node_to_str(e_envi *env, char *tmp, int *i)
{
	int j;

	j = 0;
	while (env->key[j])
	{
		tmp[i] = env->key[j];
		(*i)++;
		j++;
	}
	tmp[*i] = '=';
	(*i)++;
	j = 0;
	while (env->value[j])
	{
		tmp[*i] = env->value[j];
		(*i)++;
		j++;
	}
}

int env_size(t_envi *env)
{
	int	counter;

	counter = 0;
	while (env && env->next != NULL)
	{
		if (env->has_value == 1)
		{
			counter += ft_strlen(env->key) + 1;
			counter += ft_strlen(env->value);
			counter++;
		}
		env = env->next;
	}
	return (counter);
}

char    **env_to_arr(t_envi *env)
{
	char    *tmp;
	char    **res;
	int     i;

	i = 0;
	if (!(tmp = malloc(env_size(env)) + 1 * sizeof(char)))
		return (NULL);
	while (env && env->next != NULL)
	{
		if (env->has_value == 1)
			node_to_str(env, tmp, &i);
		if (env->next->next != NULL)
			tmp[i++] = '\n';
		env = env->next;
	}
	tmp[i] = '\0';
	res = ft_split(tmp, '\n'); //check if exists?
	free(tmp); //check if exists?
	return (res);
}

char    *find_path(char **paths, char *path, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) == 0) //check F/X
			return (path);
		free(path);
		i++;
	}
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	return (NULL);
}

void    execute_external(char **args, t_envi *env)
{
	char    **paths;
	char    **env_array;
	char    path[PATH_MAX]; //set max
	int     pid;

	path[0] = '\0';
	while (env && ft_strncmp(env->key, "PATH", 4) != 0) //do in different function
		env = env->next;
	if (env == NULL) //what is supposed to happen? or what if PATH has been unset but PATHP exported
		return ;
	paths = ft_split(env->value, ':');
	if (paths == NULL)
		error;
	path = find_path(paths, path, args[0]);
	if (!path)
		error, path not found //free paths?
	pid = fork();
	if (pid == 0)
	{
		env_array = env_to_arr(env);
		if (!env_array)
			error;
		execve(path, args, env_array);
		error, free shit
	}
}
