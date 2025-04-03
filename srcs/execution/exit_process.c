#include "../minishell.h"

void	exit_process(t_ast *ast, t_mini *lash)
{
	free_tree(ast);
	free_env(lash->env);
	if (STDIN_FILENO == lash->fd_in)
		close(fd_in);
	if (STDOUT_FILENO == lash->fd_out)
		close(fd_out);
	exit(lash->exit_code);
}
