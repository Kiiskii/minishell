#include "../minishell.h"

char	*handle_squotes(char *new_token, t_indexer *s)
{
	int	i;
	int	len;

	s->i++;
	i = s->i;
	while (s->str[i] && s->str[i] != '\'')
		i++;
	len = i - s->i;
	if (!new_token)
		new_token = ft_substr(s->str, s->i, len);
	s->i = i - 1;
	return (new_token);
}

char	*handle_dquotes(char *new_token, t_indexer *s)
{
	int	start;

	if (s->j < s->i)
		new_token = ft_strjoin(new_token, ft_substr(s->str, s->j, s->i - s->j));
	s->i++;
	start = s->i;
	while (s->str[s->i] && s->str[s->i] != '"')
		s->i++;
	new_token = ft_strjoin(new_token, ft_substr(s->str, start, s->i - start));
	s->j = s->i + 1;
	return (new_token);
}

char	*iterate_token(t_indexer *s, t_mini *lash)
{
	char	*new_token;

	(void)lash;
	new_token = "";
	while (s->str[s->i])
	{
		if (s->str[s->i] == '"')
			new_token = handle_dquotes(new_token, s);
		else if (s->str[s->i] == '\'')
			new_token = handle_squotes(new_token, s);
		s->i++;
	}
	if (new_token[0] == '\0')
		new_token = ft_strdup(s->str);
	return (new_token);
}

void	remove_quotes(t_token *tokens, t_mini *lash)
{
	t_token		*temp;
	t_indexer	s;

	temp = tokens;
	(void)lash;
	while (temp)
	{
		ft_memset(&s, 0, sizeof(t_indexer));
		if (temp->type == HEREDOC)
			temp = temp->next->next;
		s.str = ft_strdup(temp->token);
		free(temp->token);
		temp->token = iterate_token(&s, lash);
		temp = temp->next;
		free(s.str);
	}
}
