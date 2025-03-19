#include "../minishell.h"

void	modify_existing(char *str, t_envi *env)
{
	int	count;
	t_envi	*trav;

	trav = env;
	count = 0;
	while (str[count] && str[count] != '=')
		count++;
	while (trav != NULL)
	{
		if (ft_strcmp(trav->key, ft_substr(str, 0, count)) == 0)
		{
			free(trav->value);
			trav->value = strdup(str[count + 1]);
		}
		trav = trav->next;
	}
}

void	add_new(char *str, t_envi *env)
{
	t_envi	*new_node;
	int		equal;

	equal = 0;
	new_node = malloc(sizeof(t_envi));
	while (str[equal] && str[equal] != '=')
		equal++;
	if (str[equal] == '=')
		new_node = create_node(new_node, str, equal, 1);
	else
		new_node = create_node(new_node, str, equal, 0);
	add_back(env, new_node);
}

_Bool	check_existing(char *str, t_envi *env)
{
	t_envi	*trav;

	trav = env;
	while (trav != NULL)
	{
		if (ft_strcmp(trav->key, str) == 0)
			return (1);
		trav = trav->next;
	}
	return (0);
}

void	add_to_env(char *str, t_envi *env)
{
	if (check_existing(str, env))
		modify_env(str, env);
	else
		add_new(str, env);
}

void	add_to_copy(t_envi **copy, t_envi *new_node)
{
	int		comp;
	t_envi	*trav;

	trav = *copy;
	comp = ft_strcmp(new_node->key, (*copy)->key);
	if (*copy == NULL || comp < 0)
	{
		new_node->next = *copy;
		*copy = new_node;
	}
	else
	{
		while (trav->next != NULL && comp > 0)
			trav = trav->next;
		new_node->next = trav->next;
		trav->next = new_node;
	}
}

t_envi	*sort_env(t_envi *env)
{
	t_envi	*copy;
	t_envi	*trav;
	t_envi	*new_node;

	trav = env;
	copy = NULL;
	while (trav != NULL)
	{
		new_node = malloc(sizeof(t_envi));
		if (!new_node)
			return (NULL);
		copy->key = strdup(trav->key);
		copy->value = strdup(trav->value);
		copy->has_value = current->has_value;
		copy->next = NULL;
		add_to_copy(&copy, new);
		trav = trav->next;
	}
	return (copy);
}

int	print_alphabetised(t_envi *env)
{
	t_envi	*trav;
	t_envi	*alphalist;

	trav = env;
	alphalist = sort_env(env);
	if (alphalist == NULL)
		return (1);
	while (trav != NULL)
	{
		printf("declare -x ");
		if (alphalist->has_value == 1)
			printf("\"%s=%s\n\"", alphalist->key, alphalist->value);
		else
			printf("\"%s\"", alphalist->key);
		trav = trav->next;
	}
	//free copied list?
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
	else
	{
		while (array[i])
		{
			if (array[1][0] == '-' && array[1][1])
			{
				ft_putstr_fd("lash: export: ", 2);
				ft_putstr_fd(array[1], 2);
				ft_putstr_fd(": options not supported\n", 2);
				ft_putstr_fd("export: usage: export [name[=value ...]\n", 2);
				exit_code = 2;
			}
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
		return (exit_code); //testing
	}

	//check if env var already exists, in which case replace
	//create new node for env

	//if you say WORD= then value is an empty string ""
	//with "export -" -->bash: export: `-': not a valid identifier -->exit code 1 BUT FOLLOWING KEYS
	//ADDED TO LIST
	//with "export -m" bash: export: -m: invalid option\n
	//export: usage: export [-fn] [name[=value]...] or export -p err -->exit_code 2 AND FOLLOWING
	//KEY NOT ADDED TO LIST
	//if error in middle, eg. "export THIS=this -m/- HELLO=WORD" -->"bash: export: `-m': not a valid identifier"
	//and exit code 1 BUT valid keys get added to list
}
