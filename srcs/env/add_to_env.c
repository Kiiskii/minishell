#include "../minishell.h"

void	update_values(char *new, int count, t_envi *env, char *key)
{
	t_envi	*trav;
	char	*seeker;

	trav = env;
	seeker = ft_substr(key, 0, count);
	if (seeker == NULL)
	{
		ft_putstr_fd("Memory allocation failed, please exit lash\n", 2);
		return ;
	}
	while (trav != NULL)
	{
		if (ft_strcmp(trav->key, seeker) == 0)
		{
			trav->value = ft_strjoin(trav->value, new);
			if (trav-> value == NULL)
			{
				free(seeker);
				ft_putstr_fd("Memory allocation failed, please exit lash\n", 2);
				return ;
			}
		}
		trav = trav->next;
	}
	free (seeker);
}

void	append_env(char *str, int count, t_envi *env)
{
	char	*key;

	key = find_key(str);
	if (!key)
		return ;
	while (*str)
	{
		if (*str == '=')
		{
			str++;
			break ;
		}
		str++;
	}
	if (!str)
		str = "";
	update_values(str, count, env, key);
}

void	replace_env(char *str, t_envi *trav, int count)
{
	char	*seeker;

	seeker = ft_substr(str, 0, count);
	if (seeker == NULL)
	{
		ft_putstr_fd("Memory allocation failed, please exit lash\n", 2);
		return ;
	}
	while (trav != NULL)
	{
		if (ft_strcmp(trav->key, seeker) == 0)
		{
			free(trav->value);
			trav->value = ft_strdup(&str[count + 1]);
			if (trav-> value == NULL)
			{
				free(seeker);
				ft_putstr_fd("Memory allocation failed, please exit lash\n", 2);
				return ;
			}
		}
		trav = trav->next;
	}
	free(seeker);
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
	replace_env(str, trav, count);
}

int	add_to_env(char *str, t_envi *env)
{
	int	exit_code;
	int	check;

	exit_code = 0;
	check = 0;
	if (str[0] == '_' && str[1] == '\0')
		return (0);
	check = check_existing(str, env);
	if (check == 12)
	{
		ft_putstr_fd("Memory allocation failed, please exit lash\n", 2);
		return (check);
	}
	else if (check == 1)
		modify_existing(str, env);
	else
		exit_code = add_new(str, env);
	return (exit_code);
}
