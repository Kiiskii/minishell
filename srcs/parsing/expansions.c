#include "../minishell.h"

char	*handle_multiple_dollar(t_indexer *s, char *new_token)
{
	if (!new_token)
		return (NULL);
	s->j = s->i;
	while (s->str[s->i] == '$')
		s->i++;
	new_token = ft_strjoin(new_token, ft_substr(s->str, s->j, s->i - s->j));
	s->j = s->i;
	return (new_token);
}

char	*handle_exps(t_indexer *s, t_mini *lash, char *new_token)
{
	char	*word;

	if (!new_token)
		return (NULL);
	word = NULL;
	if (s->j < s->i)
		new_token = ft_strjoin(new_token, ft_substr(s->str, s->j, s->i - s->j));
	if (s->str[s->i + 1] == '?')
	{
		word = ft_itoa(lash->exit_code);
		s->i++;
	}
	else if (s->str[s->i + 1] == '$' || !s->str[s->i + 1])
		return (handle_multiple_dollar(s, new_token));
	else
		word = exps_find_key(&s->str[s->i + 1], lash->env);
	if (word)
		new_token = ft_strjoin(new_token, word);
	free(word);
	s->i += iterate_key(&s->str[s->i + 1]);
	s->j = s->i + 1;
	return (new_token);
}

char	*iterate_token_exp(t_indexer *s, t_mini *lash)
{
	char	*new_token;

	new_token = "";
	if (!s->str)
		return (NULL);
	while (s->str[s->i])
	{
		if (s->str[s->i] == '\'')
		{
			s->i += iterate_quotes(&s->str[s->i + 1], s->str[s->i]) + 1;
			new_token = ft_strjoin(new_token, ft_substr(s->str, s->j, s->i - s->j));
			s->j = s->i;
		}
		if (s->str[s->i] == '$')
			new_token = handle_exps(s, lash, new_token);
		else
			s->i++;
		if (!new_token)
			return (NULL);
	}
	if ((!new_token || new_token[0] == '\0') && s->i <= s->j)
		return (ft_strdup(""));
	if (s->j < s->i)
		new_token = ft_strjoin(new_token, ft_substr(s->str, s->j, s->i - s->j));
	return (new_token);
}

void	expand_tokens(t_token **tokens, t_mini *lash)
{
	t_token		*temp;
	t_indexer	s;

	temp = *tokens;
	while (temp)
	{
		ft_memset(&s, 0, sizeof(t_indexer));
		if (temp->type == HEREDOC)
			temp = temp->next->next;
		else
		{
			s.str = ft_strdup(temp->token);
			temp->token = iterate_token_exp(&s, lash);
			if (!temp || !temp->token)
			{
				malloc_fail_message(tokens);
				return ;
			}
			free(s.str);
			temp = temp->next;
		}
	}
}
