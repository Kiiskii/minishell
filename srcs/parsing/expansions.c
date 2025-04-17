#include "../minishell.h"

/*
char	*expansion_in_quotes(char quote, char *word, t_indexer *s)
{
}
*/

char	*find_env_match(char *my_key, t_envi *env)
{
	t_envi	*tmp;
	char	*my_value;
	int		keylen;

	tmp = env;
	keylen = ft_strlen(my_key);
	while (tmp)
	{
		if (!(ft_strncmp(my_key, tmp->key, keylen)))
		{
			my_value = ft_strdup(tmp->value);
			if (my_value == NULL)
				return (NULL);
			return (my_value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*handle_expansions(t_indexer *s, t_envi *env)
{
	char	*temp;
	char	*value;
	int		len;
	int		i;

	len = 0;
	i = s->i;
	while (ft_isalnum(s->str[s->i]))
	{
		len++;
		s->i++;
	}
	temp = malloc(len + 1);
	temp[len] = '\0';
	ft_strlcpy(temp, &s->str[s->i], len);
	value = find_env_match(temp, env);
	return (value);
}

char	*parse_expansions(char *input, t_envi *env)
{
	char		*my_input;
	char		*temp;
	t_indexer	s;

	ft_memset(&s, 0, sizeof(t_indexer));
	my_input = NULL;
	s.str = ft_strdup(input);
	while (s.str[s.i])
	{
		if (s.str[s.i] == '$')
		{
			s.i++;
			my_input = handle_expansions(&s, env);
			if (!my_input)
				my_input = ft_strdup(temp);
			return (my_input);
		}
		s.i++;
	}
	return (input);
}
