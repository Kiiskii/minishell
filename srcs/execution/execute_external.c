#include "../minishell.h"

void    node_to_str(t_envi *env, char *tmp, int *i)
{
	int j;

	j = 0;
	while (env->key[j])
	{
		tmp[*i] = env->key[j];
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

//char	**env_to_arr(t_envi *env)
//{
//	char	*res;
//	char	**arr;
//	int	size;
//
//	size = env_size(env);
//	res = malloc ((size + 1) * sizeof(char));
//	arr = ft_split(res, ' ');
//	free(res);
//	return (arr);
//}


char    **env_to_arr(t_envi *env)
{
	char    *tmp;
	char    **res;
	int     i;
	int		size;

	i = 0;
	size = env_size(env);
	if (!(tmp = malloc((size + 1) * sizeof(char))))
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
		tmp = ft_strjoin(paths[i], "/"); //TODO malloc check
		path = ft_strjoin(tmp, cmd); //TODO malloc check
		free(tmp);
		if (access(path, X_OK) == 0)
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
