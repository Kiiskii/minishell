/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillen <lguillen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:39:56 by lguillen          #+#    #+#             */
/*   Updated: 2025/05/19 10:39:57 by lguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	iterate_word(t_indexer *s)
{
	while (s->str[s->i] && !ft_isblank(s->str[s->i])
		&& !is_specialchar(s->str[s->i]))
	{
		if (s->str[s->i] == '"')
		{
			s->i++;
			while (s->str[s->i] != '"')
				s->i++;
		}
		else if (s->str[s->i] == '\'')
		{
			s->i++;
			while (s->str[s->i] != '\'')
				s->i++;
		}
		s->i++;
	}
}

int	handle_words(t_token **list, char *str)
{
	char		*word;
	t_indexer	s;

	ft_memset(&s, 0, sizeof(t_indexer));
	s.str = ft_strdup(str);
	if (!s.str)
	{
		malloc_fail_message(list);
		return (-1);
	}
	iterate_word(&s);
	word = ft_substr(s.str, 0, s.i);
	free(s.str);
	if (!word)
		return (-1);
	add_token(list, &word, WORD);
	if (!*list)
		return (-1);
	return (s.i);
}
