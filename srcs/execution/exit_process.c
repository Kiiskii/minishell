#include "../minishell.h"

void	exit_process(t_mini *lash) //(t_ast *ast, t_mini *lash)
{
	t_envi	*tmp;

//	free_tree(ast);
	tmp = lash->env;
	while (lash->env)
	{
		lash->env = lash->env->next;
		free(tmp);
		tmp = lash->env;
	}
	if (STDIN_FILENO == lash->fd_in)
		close(lash->fd_in);
	if (STDOUT_FILENO == lash->fd_out)
		close(lash->fd_out);
	exit(lash->exit_code);
}
