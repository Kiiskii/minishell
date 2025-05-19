#include "../minishell.h"

void	node_to_str(t_envi *env, char *tmp, int *i)
{
	int	j;

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

int	env_size(t_envi *env)
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

char	**env_to_arr(t_envi *env)
{
	char	*tmp;
	char	**res;
	int		i;
	int		size;

	i = 0;
	size = env_size(env);
	tmp = ft_calloc(1, (size + 1) * sizeof(char));
	if (tmp == NULL)
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
	res = ft_split(tmp, '\n');
	if (res == NULL)
		ft_putstr_fd("Cannot allocate memory, please CTRL + D!\n", 2);
	free(tmp);
	return (res);
}
