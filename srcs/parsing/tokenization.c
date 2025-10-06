/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillen <lguillen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:41:07 by lguillen          #+#    #+#             */
/*   Updated: 2025/05/19 10:41:08 by lguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_token(t_token **list, char **content, t_token_type type)
{
	t_token	*new_node;
	t_token	*tmp;

	new_node = ft_calloc(1, sizeof(t_token));
	if (!new_node || !content)
	{
		free(*content);
		malloc_fail_message(list);
		return ;
	}
	new_node->token = *content;
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
	char	*redir;

	if (str[0] == '<' && str[1] == '<')
	{
		redir = ft_strdup("<<");
		add_token(list, &redir, HEREDOC);
		return (2);
	}
	else if (str[0] == '>' && str[1] == '>')
	{
		redir = ft_strdup(">>");
		add_token(list, &redir, REDIR_APP);
		return (2);
	}
	redir = ft_substr(str, 0, 1);
	if (str[0] == '<')
		add_token(list, &redir, REDIR_IN);
	else
		add_token(list, &redir, REDIR_OUT);
	if (!*list)
		return (-1);
	return (1);
}

int	handle_special_chars(t_token **list, char *input)
{
	char	*pipe;
	int		len;

	len = 1;
	if (input[0] == '|')
	{
		pipe = ft_strdup("|");
		add_token(list, &pipe, PIPE);
	}
	else
		len = handle_redirs(list, input);
	if (!list)
		return (-1);
	return (len);
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
		if (input[i] == '\0')
			break ;
		if (is_specialchar(input[i]))
			len = handle_special_chars(list, &input[i]);
		else
			len = handle_words(list, &input[i]);
		if (len == -1)
			return ;
		i += len;
	}
}
