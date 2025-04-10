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

int	word_in_quotes(char **word, char *str, int i, int *j)
{
	int		start;
	char	quote;

	quote = str[i];
	if (*j > 1)
		*word = ft_strjoin(*word, ft_substr(str, i - *j + 1, *j - 1));
	if (i > 0 && !(*word))
		*word = ft_substr(str, 0, i);
	*j = 0;
	i++;
	start = i;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] != quote)
		printf("SYNTAX ERROR, EXIT\n");
	else
		*word = concat_word(*word, &str[start], i - start);
	return (i + 1);
}

int	handle_words(t_token **list, char *str)
{
	int		i;
	int		j;
	char	*word;

	word = NULL;
	i = 0;
	j = 0;
	while (str[i] && !ft_isblank(str[i]) && !is_specialchar(str[i]))
	{
		j++;
		if (str[i] == '"')
			i = word_in_quotes(&word, str, i, &j);
		else if (str[i] == '\'')
			i = word_in_quotes(&word, str, i, &j);
		else
			i++;
	}
	if (!word)
		word = ft_substr(str, 0, i);
	else if (j > 1)
		word = ft_strjoin(word, ft_substr(str, i - j, j));
	if (word[0] != '\0')
		add_token(list, word, WORD);
	return (i);
}
