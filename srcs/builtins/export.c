#include "../minishell.h"

//TODO: exit codes
//test that expansions work
//check cases at bottom of file

char	*find_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	if (str[i] == '=' && str[i - 1] == '+')
		i--;
	key = ft_substr(str, 0, i);
	if (!key) //check can it be other than malloc
		ft_putstr_fd("Memory allocation failed, please exit lash", 2);
	return (key);
}

void	append_env(char *str, int count, t_envi *env)
{
	t_envi	*trav;
	char	*key;

	trav = env;
	key = find_key(str);
	while (*str)
	{
		if (*str == '=')
		{
			str++;
			break ;
		}
		str++;
	}
	while (trav != NULL)
	{
		if (ft_strcmp(trav->key, ft_substr(key, 0, count)) == 0)
			trav->value = ft_strjoin(trav->value, str);
		trav = trav->next;
	}
}

int	is_valid_input(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	if (str[i] == '=' && str[i - 1] == '+')
		i--;
	key = ft_substr(str, 0, i);
	i = 0;
	while (key[i])
	{
		if (ft_isalnum(key[i]) == 0 && key[i] != '_')
		{
			ft_putstr_fd("lash: export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2); //TODO: set exit_code to 1
			return (0);
		}
		i++;
	}
	free(key);
	return (1);
}

void	modify_existing(char *str, t_envi *env)
{
	int		count;
	t_envi	*trav;

	trav = env;
	count = 0;
	if (!is_valid_input(str))
		return ;
	while (str[count] && str[count] != '=')
		count++;
	if (str[count] == '=' && str[count - 1] == '+')
	{
		count--;
		append_env(str, count, env);
		return ;
	}
	while (trav != NULL)
	{
		if (ft_strcmp(trav->key, ft_substr(str, 0, count)) == 0)
		{
			free(trav->value);
			trav->value = ft_strdup(&str[count + 1]);
		}
		trav = trav->next;
	}
}

void	add_new(char *str, t_envi *env)
{
	t_envi	*new_node;
	int		equal;

	equal = 0;
	new_node = malloc(sizeof(t_envi)); //TODO: malloc check
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

_Bool	check_existing(char *str, t_envi *env)
{
	t_envi	*trav;
	char	*key;
	int		count;

	count = 0;
	trav = env;
	while (str[count] && str[count] != '=')
		count++;
	if (str[count] == '=' && str[count - 1] == '+')
		count--;
	key = ft_substr(str, 0, count);
	while (trav != NULL)
	{
		if (ft_strcmp(trav->key, key) == 0)
			return (1);
		trav = trav->next;
	}
	free(key);
	return (0);
}

void	add_to_env(char *str, t_envi *env)
{
	if (str[0] == '_' && str[1] == '\0')
		return ;
	if (check_existing(str, env))
		modify_existing(str, env);
	else
		add_new(str, env);
}

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
		new_node->key = ft_strdup(trav->key);
		new_node->value = ft_strdup(trav->value);
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

	alphalist = sort_env(env);
	if (alphalist == NULL)
		return (1);
	while (alphalist != NULL)
	{
		printf("declare -x ");
		if (alphalist->has_value == 1)
			printf("%s=\"%s\"\n", alphalist->key, alphalist->value);
		else
			printf("\"%s\"", alphalist->key);
		alphalist = alphalist->next;
	}
	//free_list(alphalist);
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
			if (i == 1 && array[i][0] == '-' && array[1][1])
			{
				ft_putstr_fd("lash: export: ", 2);
				ft_putstr_fd(array[1], 2);
				ft_putstr_fd(": options not supported\n", 2);
				ft_putstr_fd("export: usage: export [name[=value ...]\n", 2);
				return (2);
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
