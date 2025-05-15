#include "../minishell.h"

t_envi	*create_shlvl(void)
{
	t_envi	*new_node;
	t_envi	*second_node;

	new_node = ft_calloc(1, sizeof(t_envi));
	if (!new_node)
		return (NULL);
	new_node->has_value = 1;
	new_node->key = ft_strdup("SHLVL");
	new_node->value = ft_strdup("1");
	if (!new_node->key || !new_node->value)
		return (NULL);
	second_node = ft_calloc(1, sizeof(t_envi));
	if (!second_node)
		return (NULL);
	new_node->next = second_node;
	second_node->has_value = 1;
	second_node->key = ft_strdup("_");
	second_node->value = ft_strdup("/usr/bin/env");
	if (!second_node->key || !second_node->value)
		return (NULL);
	second_node->next = NULL;
	return (new_node);
}

t_envi	*create_node(t_envi *new_node, char *env, int j, int has_value)
{
	new_node->has_value = has_value;
	new_node->key = ft_substr(env, 0, j);
	new_node->next = NULL;
	if (has_value)
		new_node->value = ft_strdup(&env[j + 1]);
	else
		new_node->value = NULL;
	return (new_node);
}

void	add_back(t_envi *tmp, t_envi *node)
{
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
	else
		tmp = node;
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
		new_node = ft_calloc(1, sizeof(t_envi));
		if (!new_node)
			return ;
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
	if (!*envi)
		*envi = create_shlvl();
}
