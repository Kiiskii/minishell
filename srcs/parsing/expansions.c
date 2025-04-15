#include "../minishell.h"

char	*handle_expansions(char *word, t_envi *env, t_indexer *s)
{
	t_envi	*tmp;
	int		key_len;

	if (s->str[s->i + 1] == '"' || s->str[s->i + 1] == '\'')
	{
		s->i++;
		return (word);
	}
	s->i++;
	tmp = env;
	printf("%s\n", &s->str[s->i]);
	while (tmp)
	{
		//printf("%s\n", tmp->key);
		key_len = ft_strlen(tmp->key);
		if ((ft_strncmp(tmp->key, &s->str[s->i], key_len)) == 0)
		{
			word = ft_strjoin(word, tmp->value);
			s->i += key_len;
			return (word);
		}
		tmp = tmp->next;
	}
	return (word);
}
