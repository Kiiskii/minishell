#include "../minishell.h"

//add heredoc after !ast check?

void	begin_execution(t_ast *ast, t_mini *lash)
{
	//printf("type: %d\n", ast->type);
	if (!ast || !lash)
		return ;
	if (ast->type == PIPE)
		execute_pipe(ast, lash);
	else if (ast->type == WORD)
		execute_command(ast, ast->args, lash);
	else if (ast->type == REDIR_IN || ast->type == REDIR_OUT
		|| ast->type == REDIR_APP)
		execute_redirs(ast, lash);
}
