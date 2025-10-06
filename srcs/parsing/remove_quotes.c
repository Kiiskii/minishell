/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillen <lguillen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:39:13 by lguillen          #+#    #+#             */
/*   Updated: 2025/05/19 10:39:14 by lguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_quotes(char *new_token, t_indexer *s, char quote)
{
	int	start;

	if (s->j < s->i)
		new_token = wrap_join(new_token, ft_substr(s->str, s->j, s->i - s->j));
	s->i++;
	start = s->i;
	while (s->str[s->i] && s->str[s->i] != quote)
		s->i++;
	new_token = wrap_join(new_token, ft_substr(s->str, start, s->i - start));
	s->j = s->i + 1;
	return (new_token);
}

char	*iterate_token(t_indexer *s, int has_quotes)
{
	char	*new_token;

	new_token = ft_strdup("");
	while (s->str[s->i])
	{
		if (s->str[s->i] == '"' || s->str[s->i] == '\'')
		{
			has_quotes = 1;
			new_token = handle_quotes(new_token, s, s->str[s->i]);
		}
		s->i++;
	}
	if (!new_token)
		return (NULL);
	if (new_token[0] == '\0' && has_quotes == 1)
		return (new_token);
	else if (new_token[0] == '\0')
	{
		free(new_token);
		new_token = ft_strdup(s->str);
	}
	else if (s->i > s->j)
		new_token = wrap_join(new_token, ft_substr(s->str, s->j, s->i - s->j));
	return (new_token);
}

void	delete_empty_token(t_token **tokens, t_token **prev, t_token **current)
{
	t_token	*tmp;

	tmp = (*current)->next;
	if (!*prev)
		*tokens = tmp;
	else
		(*prev)->next = tmp;
	free((*current)->token);
	free(*current);
	*current = tmp;
}

int	prep_quote_removal(t_token **tokens, t_token *temp)
{
	t_indexer	s;

	ft_memset(&s, 0, sizeof(t_indexer));
	s.str = temp->token;
	temp->token = iterate_token(&s, 0);
	free(s.str);
	if (!temp->token)
	{
		malloc_fail_message(tokens);
		return (-2);
	}
	return (0);
}

void	remove_quotes(t_token **tokens)
{
	t_token		*temp;
	t_token		*prev;

	temp = *tokens;
	prev = NULL;
	while (temp)
	{
		if (temp->type == HEREDOC)
		{
			prev = temp->next;
			temp = temp->next->next;
			continue ;
		}
		if (temp->token[0] == '\0')
			delete_empty_token(tokens, &prev, &temp);
		else
		{
			if (prep_quote_removal(tokens, temp) != 0)
				return ;
			prev = temp;
			temp = temp->next;
		}
	}
}
