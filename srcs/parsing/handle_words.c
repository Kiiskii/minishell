#include "../minishell.h"

void	iterate_word(t_indexer *s)
{
	while (s->str[s->i] && !ft_isblank(s->str[s->i]) && !is_specialchar(s->str[s->i]))
	{
		if (s->str[s->i] == '"')
		{
			s->i++;
			while (s->str[s->i] != '"')
				s->i++;
		}
		else if (s->str[s->i] == '\'')
		{
			s->i++;
			while (s->str[s->i] != '\'')
				s->i++;
		}
		s->i++;
	}
}

int	handle_words(t_token **list, char *str)
{
	char		*word;
	t_indexer	s;

	ft_memset(&s, 0, sizeof(t_indexer));
	s.str = str;
	word = NULL;
	iterate_word(&s);
	word = ft_substr(s.str, 0, s.i);
	add_token(list, word, WORD);
	if (!*list || !word)
		return (-1);
	return (s.i);
}
