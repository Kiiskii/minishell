#include "../minishell.h"

int	error_quotes(char *input)
{
	int	i;

	i = 0;
	while(input[i])
	{
		if (input[i] == '"')
		{
			i++;
			while(input[i] && input[i] != '"')
				i++;
			if (input[i] == '\0')
				return (0);
		}
		if (input[i] == '\'')
		{
			i++;
			while(input[i] && input[i] != '\'')
				i++;
			if (input[i] == '\0')
				return (0);
		}
		i++;
	}
	return (1);
}

int	error_pipe_end(char *input)
{
	int	last;

	last =  ft_strlen(input) - 1;
	if (input[last] == '|')
		return (0);
	return (1);
}

int	error_input(char *input, t_mini *lash)
{
	int	error;

	error = error_quotes(input);
	if (error == 0)
	{
		ft_putstr_fd("lash: syntax error: unclosed quotes\n", 2);
		lash->exit_code = 2;
		return (0);
	}
	error = error_pipe_end(input);
	if (error == 0)
	{
		ft_putstr_fd("lash: syntax error: input ends in `|'\n", 2);
		lash->exit_code = 2;
		return (0);
	}
	return (1);
}

int	error_redir(t_token *tokens, t_mini *lash)
{
	if (tokens->next->type != WORD)
	{
		if (tokens->type >= REDIR_IN && tokens->type <= REDIR_APP)
		{
			ft_putstr_fd("lash: syntax error near unexpected token `", 2);
			ft_putstr_fd(tokens->next->token, 2);
			ft_putstr_fd("'\n", 2);
			lash->exit_code = 2;
			return (0);
		}
		if (tokens->type >= PIPE)
		{
			ft_putstr_fd("lash: syntax error near unexpected token `", 2);
			ft_putstr_fd(tokens->token, 2);
			ft_putstr_fd("'\n", 2);
			lash->exit_code = 2;
			return (0);
		}
	}
	return (1);
}

int	error_token(t_token *tokens, t_mini *lash)
{
	int	error;
	t_token *tmp;

	tmp = tokens;
	error = 1;
	while (tmp)
	{
		if (tmp->type >= PIPE && tmp->type <= REDIR_APP)
			error = error_redir(tokens, lash);
		if (error == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
