#include "../minishell.h"

int	is_valid_input(char *str)
{
	int		i;
	char	*key;

	i = 0;
	key = find_key(str);
	if (key[i] == '\0')
	{
		ft_putstr_fd("lash: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	while (key[i])
	{
		if (ft_isalnum(key[i]) == 0 && key[i] != '_')
		{
			ft_putstr_fd("lash: export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	free(key);
	return (1);
}

void	add_new(char *str, t_envi *env)
{
	t_envi	*new_node;
	int		equal;

	equal = 0;
	new_node = malloc(sizeof(t_envi));
	if (!new_node)
		printf("Memory allocation failed, please exit lash\n");
	if (!is_valid_input(str))
		return ;
	while (str[equal] && str[equal] != '=')
		equal++;
	if (str[equal] == '=')
		new_node = create_node(new_node, str, equal, 1);
	else
		new_node = create_node(new_node, str, equal, 0);
	add_back(env, new_node);
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

int	builtin_export(char **array, t_envi *env)
{
	int		i;
	int		exit_code;

	i = 1;
	exit_code = 0;
	if (!array[i])
		return (print_alphabetised(env));
	while (array[i])
	{
		if (i == 1 && check_option(array) == 1)
			return (2);
		else if (array[i][0] == '-')
		{
			ft_putstr_fd("lash: export: '", 2);
			ft_putstr_fd(array[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_code = 1;
		}
		else
			add_to_env(array[i], env);
		i++;
	}
	return (exit_code);
}
