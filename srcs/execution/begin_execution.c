#include "../minishell.h"

void	begin_execution(t_ast *ast, t_mini *lash)
{
	if (!ast || !lash)
		return ;
	if (ast->type == PIPE)
		execute_pipe(ast, lash);
	else if (ast->type == WORD)
		execute_command(ast->args, lash);
	else if (ast->type == REDIR_IN || ast->type == REDIR_OUT
		|| ast->type == REDIR_APP) //HEREDOC can you say >= REDIR_IN && <= REDIR_APP
		execute_redirs(ast, lash);
}
