#include "../minishell.h"

void	add_to_copy(t_envi **copy, t_envi *new_node)
{
	int		comp;
	t_envi	*trav;

	if (*copy == NULL)
	{
		*copy = new_node;
		return ;
	}
	trav = *copy;
	comp = ft_strcmp(new_node->key, trav->key);
	if (comp < 0)
	{
		new_node->next = *copy;
		*copy = new_node;
	}
	else
	{
		while (trav->next != NULL
			&& ft_strcmp(new_node->key, trav->next->key) > 0)
			trav = trav->next;
		new_node->next = trav->next;
		trav->next = new_node;
	}
}

t_envi	*sort_env(t_envi *env, t_envi *copy)
{
	t_envi	*trav;
	t_envi	*new_node;

	trav = env;
	while (trav != NULL)
	{
		new_node = malloc(sizeof(t_envi));
		if (!new_node)
			return (NULL);
		new_node->key = ft_strdup(trav->key);
		if (new_node->key == NULL)
			return (NULL);
		if (trav->has_value)
		{
			new_node->value = ft_strdup(trav->value);
			if (new_node->value == NULL)
				return (NULL);
		}
		new_node->has_value = trav->has_value;
		new_node->next = NULL;
		add_to_copy(&copy, new_node);
		trav = trav->next;
	}
	return (copy);
}

int	print_alphabetised(t_envi *env)
{
	t_envi	*alphalist;
	t_envi	*copy;

	copy = NULL;
	alphalist = sort_env(env, copy);
	if (!alphalist)
	{
		ft_putstr_fd("Memory allocation failed, please exit lash\n", 2);
		return (12);
	}
	while (alphalist != NULL)
	{
		printf("declare -x ");
		if (alphalist->has_value == 1)
			printf("%s=\"%s\"\n", alphalist->key, alphalist->value);
		else
			printf("%s\n", alphalist->key);
		alphalist = alphalist->next;
	}
	free_list(&alphalist);
	return (0);
}
