#include "../minishell.h"

char	*concat_word(char *word, char *str, int len)
{
	char	*new_word;
	char	*tmp;

	tmp = ft_substr(str, 0, len);
	if (!word)
		return (tmp);
	new_word = ft_strjoin(word, tmp);
	free(tmp);
	free(word);
	return (new_word);
}

char	*word_in_quotes(char *word, t_indexer *s)
{
	int		start;
	char	quote;

	quote = s->str[s->i];
	if (s->j > 1)
		word = ft_strjoin(word, ft_substr(s->str, s->i - s->j + 1, s->j - 1));
	if (s->i > 0 && !word)
		word = ft_substr(s->str, 0, s->i);
	s->j = 0;
	s->i++;
	start = s->i;
	while (s->str[s->i] && s->str[s->i] != quote)
		s->i++;
	word = concat_word(word, &s->str[start], s->i - start);
	s->i++;
	return (word);
}

char	*iterate_word(t_indexer *s)
{
	char	*word;

	word = NULL;
	while (s->str[s->i] && !ft_isblank(s->str[s->i]) && !is_specialchar(s->str[s->i]))
	{
		s->j++;
		if (s->str[s->i] == '"')
			word = word_in_quotes(word, s);
		else if (s->str[s->i] == '\'')
			word = word_in_quotes(word, s);
		/*
		else if (s->str[s->i] == '$')
			word = handle_expansions(word, env, s);
		*/
		else
			s->i++;
	}
	return (word);
}

int	handle_words(t_token **list, char *str)
{
	char		*word;
	t_indexer	s;

	ft_memset(&s, 0, sizeof(t_indexer));
	s.str = ft_strdup(str);
	word = NULL;
	word = iterate_word(&s);
	if (!word)
		word = ft_substr(s.str, 0, s.i);
	else if (s.j > 1)
		word = ft_strjoin(word, ft_substr(s.str, s.i - s.j, s.j));
	if (word[0] != '\0')
		add_token(list, word, WORD);
	free(s.str);
	return (s.i);
}
