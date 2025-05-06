#include "../minishell.h"

void	replace_tokens(t_token **current, t_token *new_tokens)
{
	t_token	*temp;
	t_token	*temp2;

	temp = (*current)->next;
	temp2 = new_tokens;
	free((*current)->token);
	(*current)->token = new_tokens->token;
	(*current)->next = new_tokens->next;
	while (new_tokens->next)
	{
		new_tokens = new_tokens->next;
	}
	new_tokens->next = temp;
	free(temp2);
}

void	add_next_token(t_token **new_tokens, char *word, int *malloc_fail)
{
	t_token	*new_node;
	t_token	*tmp;

	new_node = malloc(sizeof(t_token));
	if (!new_node || !word)
	{
		*malloc_fail = 1;
		free_tokens(new_tokens);
		return ;
	}
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

void	parse_token(t_token *current, int i, int j, int *malloc_fail)
{
	char	*word;
	t_token	*new_tokens;

	new_tokens = NULL;
	while (current->token[i])
	{
		if (current->token[i] == '"' || current->token[i] == '\'')
			i += iterate_quotes(&current->token[i + 1], current->token[i]);
		else if (ft_isblank(current->token[i]))
		{
			word = ft_substr(current->token, j, i - j);
			add_next_token(&new_tokens, word, malloc_fail);
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
		add_next_token(&new_tokens, word, malloc_fail);
	}
	replace_tokens(&current, new_tokens);
}

void	re_tokenize(t_token **tokens)
{
	t_token		*temp;
	int			malloc_fail;

	temp = *tokens;
	malloc_fail = 0;
	while (temp)
	{
		if (temp->type == HEREDOC)
			temp = temp->next->next;
		else
		{
			parse_token(temp, 0, 0, &malloc_fail);
			if (malloc_fail == 1)
			{
				free_tokens(tokens);
				tokens = NULL;
				ft_putstr_fd("Cannot allocate memory, please exit lash!\n", 2);
				return ;
			}
			temp = temp->next;
		}
	}
}
