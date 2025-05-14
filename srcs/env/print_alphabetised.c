#include "../minishell.h"

static void	add_to_copy(t_envi **copy, t_envi *new_node)
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

static int	add_data(t_envi *env, t_envi *new_node, t_envi *copy)
{
	new_node->key = ft_strdup(env->key);
	if (new_node->key == NULL)
	{
		free(new_node);
		free_env(copy);
		return (1);
	}
	if (env->has_value)
	{
		new_node->value = ft_strdup(env->value);
		if (new_node->value == NULL)
		{
			free(new_node->key);
			free(new_node);
			free_env(copy);
			return (1);
		}
	}
	return (0);
}

static t_envi	*sort_env(t_envi *env, t_envi *copy)
{
	t_envi	*new_node;

	while (env != NULL)
	{
		new_node = ft_calloc(1, sizeof(t_envi));
		if (!new_node)
		{
			free_env(copy);
			return (NULL);
		}
		if (add_data(env, new_node, copy) == 1)
			return (NULL);
		new_node->has_value = env->has_value;
		new_node->next = NULL;
		add_to_copy(&copy, new_node);
		env = env->next;
	}
	return (copy);
}

int	print_alphabetised(t_envi *env)
{
	t_envi	*alphalist;
	t_envi	*copy;
	t_envi	*trav;

	copy = NULL;
	alphalist = sort_env(env, copy);
	if (!alphalist)
	{
		ft_putstr_fd("Cannot allocate memory, please CTRL + D!\n", 2);
		return (1);
	}
	trav = alphalist;
	while (trav != NULL)
	{
		printf("declare -x ");
		if (trav->has_value == 1)
			printf("%s=\"%s\"\n", trav->key, trav->value);
		else
			printf("%s\n", trav->key);
		trav = trav->next;
	}
	free_env(alphalist);
	return (0);
}
