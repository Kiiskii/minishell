#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

void	add_token(t_token **list, char *content, t_token_type type)
{
	t_token	*new_node;
	t_token	*tmp;

	new_node = malloc(sizeof(t_list));
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

int	is_specialchar(char c)
{
	if (c == '|')
		return (1);
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

void	tokenize_input(char *input, t_token **list)
{
	int	i;
	int	start;
	int	len;

	i = 0;
	while (input[i])
	{
		len = 0;
		while (ft_iswhitespace(input[i]))
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
		{
			start = i;
			while (input[i] && !ft_iswhitespace(input[i]) && !is_specialchar(input[i]))
				i++;
			add_token(list, ft_substr(input, start, i - start), WORD);
		}
		i += len;
	}
}

int	main()
{
	char	*input;
	t_token	*tokens;
	t_token	*tmp;

	tokens = NULL;
	while (1)
	{
		input = readline("lash$: ");
		if (!input)
		{
			printf("\nExiting lash...\n");
			break ;
		}
		tokenize_input(input, &tokens);
		tmp = tokens;
		while (tmp)
		{
			printf("Token: %s, Type: %d\n", tmp->token, tmp->type);
			tmp = tmp->next;
		}
		free(input);
	}
	return (0);
}
