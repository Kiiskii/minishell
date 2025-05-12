#include "../minishell.h"

void	exit_process(t_mini *lash)
{
	if (lash->fd_in != -1)
		close(lash->fd_in);
	if (lash->head)
		free_ast(lash->head);
	free_env(lash->env);
	exit(lash->exit_code);
}
