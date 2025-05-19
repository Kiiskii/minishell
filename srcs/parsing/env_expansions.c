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
			my_value = ft_strdup(tmp->value);//
			if (!my_value)
				return (NULL);
			return (my_value);
		}
		tmp = tmp->next;
	}
	my_value = ft_strdup("");
	if (!my_value)
		return (NULL);
	return (my_value);
}

char	*exps_find_key(char *token, t_envi *env)
{
	char	*value;
	char	*my_key;
	int		i;

	i = 0;
	while (ft_isalnum(token[i]) || token[i] == '_')
		i++;
	my_key = ft_substr(token, 0, i);
	if (!my_key)
		return (NULL);
	value = find_env_match(my_key, env);
	free(my_key);
	return (value);
}
