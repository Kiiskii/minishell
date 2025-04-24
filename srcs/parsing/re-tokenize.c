#include "../minishell.h"

void	replace_tokens(t_token **current, t_token *new_tokens)
{
	t_token	*temp;
	t_token	*temp2;

	temp = (*current)->next;
	temp2 = new_tokens;
	(*current)->token = new_tokens->token;
	(*current)->next = new_tokens->next;
	printf("replace newtoken: %s\n", new_tokens->token);
	while (new_tokens->next)
	{
		printf("replace: %s\n", new_tokens->token);
		new_tokens = new_tokens->next;
	}
	new_tokens->next = temp;
	free(temp2);
}

void	add_next_token(t_token **new_tokens, char *word)
{
	t_token	*new_node;
	t_token	*tmp;

	printf("HERE\n");
	new_node = malloc(sizeof(t_token));
	if (!new_node)
		printf("MALLOC FAIL\n");
	new_node->token = word;
	new_node->type = WORD;
	new_node->next = NULL;
	if (!(*new_tokens))
		*new_tokens = new_node;
	else
	{
		tmp = *new_tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

int	iterate_quotes(char *str, char quote)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}

void	parse_token(t_token *current, t_mini *lash)
{
	int		i;
	int		j;
	char	*word;
	t_token	*new_tokens;

	i = 0;
	j = 0;
	(void)lash;
	new_tokens = NULL;
	while (current->token[i])
	{
		if (current->token[i] == '"' || current->token[i] == '\'')
			i += iterate_quotes(&current->token[i + 1], current->token[i]);
		else if (ft_isblank(current->token[i]))
		{
			word = ft_substr(current->token, j, i - j);
			add_next_token(&new_tokens, word);
			i += iterate_quotes(&current->token[i], current->token[i]);
			j = i + 1;
		}
		i++;
	}
	if (!new_tokens)
		return ;
	if (j < i)
	{
		word = ft_substr(current->token, j, i - j);
		add_next_token(&new_tokens, word);
	}
	replace_tokens(&current, new_tokens);
}

void	re_tokenize(t_token *tokens, t_mini *lash)
{
	t_token		*temp;

	temp = tokens;
	while (temp)
	{
		if (temp->type == HEREDOC)
			temp = temp->next->next;
		parse_token(temp, lash);
		temp = temp->next;
	}
}
