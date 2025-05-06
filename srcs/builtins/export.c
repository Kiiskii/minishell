#include "../minishell.h"

int	is_valid_input(char *str)
{
	int		i;
	char	*key;

	i = 0;
	key = find_key(str);
	if (key == NULL)
		return (12);
	if (key[i] == '\0')
	{
		not_valid_msg(str);
		return (0);
	}
	while (key[i])
	{
		if (ft_isalnum(key[i]) == 0 && key[i] != '_')
		{
			not_valid_msg(str);
			return (0);
		}
		i++;
	}
	free(key);
	return (1);
}

int	add_new(char *str, t_envi *env)
{
	t_envi	*new_node;
	int		equal;
	int		exit_code;

	equal = 0;
	exit_code = 0;
	new_node = malloc(sizeof(t_envi));
	if (!new_node)
	{
		printf("Memory allocation failed, please exit lash\n");
		return (12);
	}
	if (is_valid_input(str) == 0)
		return (1);
	else if (is_valid_input(str) == 12)
		return (12);
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

int	check_option(char **array)
{
	if (array[1][0] == '-' && array[1][1])
	{
		ft_putstr_fd("lash: export: ", 2);
		ft_putstr_fd(array[1], 2);
		ft_putstr_fd(": options not supported\n", 2);
		ft_putstr_fd("export: usage: export [name[=value ...]\n", 2);
		return (1);
	}
	return (0);
}

void	builtin_export(char **array, t_envi *env, t_mini *lash)
{
	int		i;
	int		exit_code;

	i = 1;
	exit_code = 0;
	if (!array[i])
	{
		lash->exit_code = (print_alphabetised(env));
		return ;
	}
	while (array[i])
	{
		if (i == 1 && check_option(array) == 1)
		{
			lash->exit_code = 2;
			return ;
		}
		else
			exit_code = add_to_env(array[i], env);
		if (exit_code == 1)
			lash->exit_code = 1;
		i++;
	}
	if (lash->exit_code != 1)
		lash->exit_code = 0;
}
