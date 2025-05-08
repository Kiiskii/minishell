#include "../minishell.h"

static int	check_key_valid(char *key, int i, char *str)
{
	while (key[i])
	{
		if (ft_isalnum(key[i]) == 0 && key[i] != '_')
		{
			not_valid_msg(str);
			free(key);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	is_valid_input(char *str)
{
	int		i;
	char	*key;

	i = 0;
	key = find_key(str);
	if (key == NULL)
	{
		ft_putstr_fd("Memory allocation failed, please exit lash\n", 2);
		return (0);
	}
	if (key[0] == '\0')
	{
		not_valid_msg(str);
		free(key);
		return (0);
	}
	if (check_key_valid(key, i, str) == 0)
		return (0);
	free(key);
	return (1);
}

static int	only_numbers(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	not_valid_msg(str);
	return (1);
}

int	add_new_env(char *str, t_envi *env)
{
	t_envi	*new_node;
	int		equal;

	equal = 0;
	new_node = malloc(sizeof(t_envi));
	if (!new_node)
		return (12);
	if (is_valid_input(str) == 0)
		return (1);
	if (only_numbers(str) == 1)
		return (1);
	while (str[equal] && str[equal] != '=')
		equal++;
	if (str[equal] == '=')
		new_node = create_node(new_node, str, equal, 1);
	else
		new_node = create_node(new_node, str, equal, 0);
	if (new_node == NULL)
		return (12);
	add_back(env, new_node);
	return (0);
}
