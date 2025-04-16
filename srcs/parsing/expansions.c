#include "../minishell.h"

char	*expansion_in_quotes(char quote, char *word, t_indexer *s)
{
}

char	*handle_expansions(char *word, t_envi *env, t_indexer *s)
{
	t_envi	*tmp;
	int		key_len;

	s->i++;
	s->j = 0;
	if (s->str[s->i] == '"' || s->str[s->i] == '\'')
		return (word);
	tmp = env;
	while (tmp)
	{
		key_len = ft_strlen(tmp->key);
		if ((ft_strncmp(tmp->key, &s->str[s->i], key_len)) == 0)
		{
			if (!word)
				word = ft_strdup(tmp->value);
			else
				word = ft_strjoin(word, tmp->value);
			s->i += ft_strlen(tmp->key);
			return (word);
		}
		tmp = tmp->next;
	}
	return (word);
}
