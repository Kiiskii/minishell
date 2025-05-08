#include "../minishell.h"

void	exit_process(t_ast *ast, t_mini *lash)
{
	free_ast(ast);
	free_env(lash->env);
	exit(lash->exit_code);
}
