#include "../minishell.h"

char	*find_env_match(char *my_key, t_envi *env)
{
	t_envi	*tmp;
	char	*my_value;
	int		keylen;

	tmp = env;
	keylen = ft_strlen(my_key);
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

char	*find_key(char *token, t_envi *env)
{
	char	*value;
	int		i;

	i = 0;
	while (ft_isalnum(token[i]) || token[i] == '_')
		i++;
	value = find_env_match(ft_substr(token, 0, i), env);
	return (value);
}

int	iterate_key(char *token)
{
	int	i;

	i = 0;
	while (ft_isalnum(token[i]) || token[i] == '_')
		i++;
	return (i);
}

char	*iterate_token_exp(char *token, t_envi *env)
{
	char	*word;
	char	*new_token;
	int		i;
	int		start;
	
	word = NULL;
	new_token = "";
	i = 0;
	start = 0;
	while (token[i])
	{
		if (token[i] == '\'')
		{
			i++;
			while (token[i] && token[i] != '\'')
				i++;
			new_token = ft_strjoin(new_token, ft_substr(token, start, i - start));
			start = i;
		}
		if (token[i] == '$')
		{
			if (start < i)
				new_token = ft_strjoin(new_token, ft_substr(token, start, i - start));
			word = find_key(&token[i + 1], env);
			if (word)
			{
				new_token = ft_strjoin(new_token, word);
				free(word);
			}
			i += iterate_key(&token[i + 1]);
			start = i + 1;
		}
		else
			i++;
	}
	if (start < i)
		new_token = ft_strjoin(new_token, ft_substr(token, start, i - start));
	if (!new_token)
		return ("");
	return (new_token);
}

void	expand_tokens(t_token *tokens, t_envi *env)
{
	t_token		*temp;

	temp = tokens;
	while (temp)
	{
		if (temp->type == HEREDOC)
			temp = temp->next->next;
		//free(temp->token);
		temp->token = iterate_token_exp(temp->token, env);
		temp = temp->next;
	}
}
