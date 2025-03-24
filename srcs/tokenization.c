#include "../minishell.h"

void	add_token(t_token **list, char *content, t_token_type type)
{
	t_token	*new_node;
	t_token	*tmp;

	new_node = malloc(sizeof(t_list));
	/*
	if (!new_node)
		return (NULL);
	*/
	new_node->token = content;
	new_node->type = type;
	new_node->next = NULL;
	if (!*list)
		*list = new_node;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

int	handle_redirs(t_token **list, char *str)
{
	if (str[0] == '<' && str[1] == '<')
	{
		add_token(list, ft_strdup("<<"), HEREDOC);
		return (2);
	}
	else if (str[0] == '>' && str[1] == '>')
	{
		add_token(list, ft_strdup(">>"), REDIR_OUT_APPEND);
		return (2);
	}
	else if (str[0] == '<')
		add_token(list, ft_strdup("<"), REDIR_IN);
	else
		add_token(list, ft_strdup(">"), REDIR_OUT);
	return (1);
}

char	*concat_word(char *word, char *str, int len)
{
	char *new_word;
	char *tmp;

	tmp = ft_substr(str, 0, len);
	if (!word)
		return (tmp);
	new_word = ft_strjoin(word, tmp);
	free(tmp);
	free(word);
	return (new_word);
}

int	handle_words(t_token **list, char *str)
{
	int		i;
	int		j;
	int		start;
	char	*word;

	word = NULL;
	i = 0;
	while (str[i] && !ft_isblank(str[i]) && !is_specialchar(str[i]))
	{
		if (str[i] == '"')
		{
			if (j > 1)
				word = ft_strjoin(word, ft_substr(str, i - j + 1, j - 1));
			j = 0;
			if (i > 0 && !word)
				word = ft_substr(str, 0, i);
			i++;
			start = i;
			while (str[i] && str[i] != '"')
				i++;
			word = concat_word(word, &str[start], i - start);
		}
		else if (str[i] == '\'')
		{
			if (j > 1)
				word = ft_strjoin(word, ft_substr(str, i - j + 1, j - 1));
			j = 0;
			if (i > 0 && !word)
				word = ft_substr(str, 0, i);
			i++;
			start = i;
			while (str[i] && str[i] != '\'')
				i++;
			word = concat_word(word, &str[start], i - start);
		}
		if (str[i])
			i++;
		j++;
	}
	if (!word)
		word = ft_substr(str, 0, i);
	if (j != 0)
		word = ft_strjoin(word, ft_substr(str, i - j + 1, j));
	add_token(list, word, WORD);
	return (i);
}

void	tokenize_input(char *input, t_token **list)
{
	int	i;
	int	len;

	i = 0;
	while (input[i])
	{
		len = 0;
		while (ft_isblank(input[i]))
			i++;
		if (is_specialchar(input[i]))
		{
			if (input[i] == '|')
			{
				add_token(list, ft_strdup("|"), PIPE);
				i++;
			}
			else
				len = handle_redirs(list, &input[i]);
		}
		else
			len = handle_words(list, &input[i]);
		i += len;
	}
}
