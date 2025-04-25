#include "../minishell.h"

char	*find_env_match(char *my_key, t_envi *env)
{
	t_envi	*tmp;
	char	*my_value;

	tmp = env;
	while (tmp)
	{
		if (!(ft_strcmp(my_key, tmp->key)))
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

char	*exps_find_key(char *token, t_envi *env)
{
	char	*value;
	int		i;

	i = 0;
	while (ft_isalnum(token[i]) || token[i] == '_')
		i++;
	value = find_env_match(ft_substr(token, 0, i), env);
	return (value);
}

char	*handle_exps(t_indexer *s, t_mini *lash, char *new_token)
{
	char	*word;

	if (s->j < s->i)
		new_token = ft_strjoin(new_token, ft_substr(s->str, s->j, s->i - s->j));
	if (s->str[s->i + 1] == '?')
	{
		word = ft_itoa(lash->exit_code);
		s->i++;
	}
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
	while (s->str[s->i])
	{
		if (s->str[s->i] == '\'')
		{
			s->i++;
			while (s->str[s->i] && s->str[s->i] != '\'')
				s->i++;
			new_token = ft_strjoin(new_token, ft_substr(s->str, s->j, s->i - s->j));
			s->j = s->i;
		}
		if (s->str[s->i] == '$')
		{
			new_token = handle_exps(s, lash, new_token);
		}
		else
			s->i++;
	}
	if (!new_token || new_token[0] == '\0')
		return (s->str);
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
		s.str = temp->token;
		//free(temp->token);
		temp->token = iterate_token_exp(&s, lash);
		//free(s.str);
		temp = temp->next;
	}
}
