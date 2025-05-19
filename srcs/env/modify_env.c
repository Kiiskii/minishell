#include "../minishell.h"

static void	update_values(char *new, t_envi *env, char *key)
{
	t_envi	*trav;
	char	*tmp;

	tmp = NULL;
	trav = env;
	(void)new;
	while (trav != NULL)
	{
		if (ft_strcmp(trav->key, key) == 0)
		{
			tmp = trav->value;
			trav->value = ft_strjoin(trav->value, new);
			free(tmp);
			if (trav-> value == NULL)
			{
				free(key);
				ft_putstr_fd("Cannot allocate memory, please CTRL + D!\n", 2);
				return ;
			}
		}
		trav = trav->next;
	}
	free(key);
}

static void	append_env(char *str, t_envi *env)
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
	update_values(str, env, key);
}

static void	replace_env(char *str, t_envi *trav, int count)
{
	char	*seeker;

	seeker = ft_substr(str, 0, count);
	if (seeker == NULL)
	{
		ft_putstr_fd("Cannot allocate memory, please CTRL + D!\n", 2);
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
				trav->has_value = 0;
				ft_putstr_fd("Cannot allocate memory, please CTRL + D!\n", 2);
				return ;
			}
		}
		trav = trav->next;
	}
	free(seeker);
}

static void	modify_existing(char *str, t_envi *env)
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
		append_env(str, env);
		return ;
	}
	replace_env(str, trav, count);
}

int	modify_env(char *str, t_envi *env)
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
		ft_putstr_fd("Cannot allocate memory, please CTRL + D!\n", 2);
		return (check);
	}
	else if (check == 1)
		modify_existing(str, env);
	else
	{
		exit_code = add_new_env(str, env);
		if (exit_code == 12)
			ft_putstr_fd("Cannot allocate memory, please CTRL + D!\n", 2);
	}
	return (exit_code);
}
