#include "../minishell.h"

t_envi	*create_node(t_envi *new_node, char *env, int j, int has_value)
{
	new_node->key = ft_substr(env, 0, j);
	new_node->next = NULL;
	if (has_value)
		new_node->value = ft_strdup(&env[j + 1]);
	else
		new_node->value = NULL;
	return (new_node);
}

void	add_back(t_envi *tmp, t_envi *new)
{
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		tmp = new;
}

void	env_to_list(t_envi **envi, char **env)
{
	int		i;
	int		j;
	t_envi	*new_node;

	i = 0;
	while (env[i])
	{
		j = 0;
		new_node = malloc(sizeof(t_envi));
		//if (!new_node)
		//	return (NULL);
		while (env[i][j] && env[i][j] != '=')
			j++;
		if (env[i][j] == '=')
			new_node = create_node(new_node, env[i], j, 1);
		else
			new_node = create_node(new_node, env[i], j, 0);
		if (!*envi)
			*envi = new_node;
		else
			add_back(*envi, new_node);
		i++;
	}
}
