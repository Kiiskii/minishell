#include "../minishell.h"

void	begin_execution(t_ast *node, t_mini *lash)
{
	if (!node || !lash)
		return ;
	if (node->type == PIPE)
		execute_pipe(node, lash);
	else if (node->type == WORD)
		execute_command(node, node->args, lash);
	else if (node->type == REDIR_IN || node->type == REDIR_OUT
		|| node->type == REDIR_APP)
		execute_redirs(node, lash);
}
