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

char	*handle_dquotes(char *new_token, t_indexer *s, t_envi *env)
{
	int	i;
	int	len;

	s->i++;
	i = s->i;
	(void)env;
	while (s->str[i] && s->str[i] != '"')
		i++;
	len = i - s->i;
	if (!new_token)
		new_token = ft_substr(s->str, s->i, len);
	s->i = i - 1;
	return (new_token);
}

char	*iterate_token(t_indexer *s, t_envi *env)
{
	char	*new_token;

	new_token = NULL;
	while (s->str[s->i])
	{
		if (s->str[s->i] == '"')
			new_token = handle_dquotes(new_token, s, env);
		else if (s->str[s->i] == '\'')
			new_token = handle_squotes(new_token, s);
		s->i++;
	}
	if (!new_token)
		new_token = ft_strdup(s->str);
	return (new_token);
}

void	re_tokenize(t_token *tokens, t_envi *env)
{
	t_token		*temp;
	t_indexer	s;

	temp = tokens;
	ft_memset(&s, 0, sizeof(t_indexer));
	while (temp)
	{
		if (temp->type == HEREDOC)
			temp = temp->next->next;
		s.str = ft_strdup(temp->token);
		free(temp->token);
		temp->token = iterate_token(&s, env);
		temp = temp->next;
		free(s.str);
	}
}
