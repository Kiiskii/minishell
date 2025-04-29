#include "../minishell.h"

char	*find_env_match(char *my_key, t_envi *env)
{
	t_envi	*tmp;
	char	*my_value;

	tmp = env;
	while (tmp)
	{
		if (!(ft_strcmp(my_key, tmp->key)))
		{
			my_value = ft_strdup(tmp->value);
			if (!my_value)
				return (NULL);
			return (my_value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*exps_find_key(char *token, t_envi *env)
{
	char	*value;
	int		i;

	i = 0;
	while (ft_isalnum(token[i]) || token[i] == '_')
		i++;
	value = find_env_match(ft_substr(token, 0, i), env);
	return (value);
}
