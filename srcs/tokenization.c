#include "../minishell.h"

void	add_token(t_token **list, char *content, t_token_type type)
{
	t_token	*new_node;
	t_token	*tmp;

	new_node = malloc(sizeof(t_token));
	/*
	if (!new_node)
		return (NULL);
	*/
	new_node->token = content;
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
	if (str[0] == '<' && str[1] == '<')
	{
		add_token(list, ft_strdup("<<"), HEREDOC);
		return (2);
	}
	else if (str[0] == '>' && str[1] == '>')
	{
		add_token(list, ft_strdup(">>"), REDIR_OUT_APPEND);
		return (2);
	}
	else if (str[0] == '<')
		add_token(list, ft_strdup("<"), REDIR_IN);
	else
		add_token(list, ft_strdup(">"), REDIR_OUT);
	return (1);
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
		if (is_specialchar(input[i]))
		{
			if (input[i] == '|')
			{
				add_token(list, ft_strdup("|"), PIPE);
				i++;
			}
			else
				len = handle_redirs(list, &input[i]);
		}
		else
			len = handle_words(list, &input[i]);
		i += len;
	}
}
