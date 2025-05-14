#include "../minishell.h"

void	error_redir(t_token *tokens, t_mini *lash)
{
	if (tokens->next == NULL)
	{
		ft_putstr_fd("lash: syntax error near unexpected token `", 2);
		ft_putstr_fd("`newline'", 2);
		ft_putstr_fd("'\n", 2);
		lash->exit_code = 2;
	}
	else
	{
		ft_putstr_fd("lash: syntax error near unexpected token `", 2);
		ft_putstr_fd(tokens->next->token, 2);
		ft_putstr_fd("'\n", 2);
		lash->exit_code = 2;
	}
}

int	error_token(t_token *tokens, t_mini *lash)
{
	if (!tokens->next || tokens->next->type != WORD)
	{
		if (tokens->type >= REDIR_IN && tokens->type <= REDIR_APP)
		{
			error_redir(tokens, lash);
			return (0);
		}
		else if (tokens->type == PIPE && tokens->next->type == PIPE)
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

int	error_iterate_list(t_token *tokens, t_mini *lash)
{
	int		heredoc_count;
	int		error;
	t_token	*tmp;

	tmp = tokens;
	error = 1;
	heredoc_count = 0;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			heredoc_count++;
		if (heredoc_count > HEREDOC_MAX)
		{
			ft_putstr_fd("lash: syntax error: too many heredocs\n", 2);
			lash->exit_code = 2;
			return (0);
		}
		if (tmp->type >= PIPE && tmp->type <= REDIR_APP)
			error = error_token(tmp, lash);
		if (error == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
