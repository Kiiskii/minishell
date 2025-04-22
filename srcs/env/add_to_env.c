#include "../minishell.h"

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
	if (key == NULL)
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

void	modify_existing(char *str, t_envi *env)
{
	int		count;
	t_envi	*trav;

	trav = env;
	count = 0;
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

int	add_to_env(char *str, t_envi *env)
{
	int	exit_code;

	exit_code = 0;
	if (str[0] == '_' && str[1] == '\0')
		return (0);
	if (check_existing(str, env))
		modify_existing(str, env);
	else
		exit_code = add_new(str, env);
	return (exit_code);
}
