#include "../minishell.h"

static void	exec_ext_child(t_mini *lash, char *path, t_ast *ast)
{
	char	**env_array;

	close(lash->fd_in);
	reset_default_signals();
	env_array = env_to_arr(lash->env);
	if (!env_array)
		ft_putstr_fd("Cannot allocate memory, please exit lash\n", 2);
	execve(path, ast->args, env_array);
	ft_putstr_fd("Failed to execute\n", 2);
	lash->exit_code = 127;
	if (errno == EACCES)
		lash->exit_code = 126;
	free_arr(env_array);
}

void	execute_external(t_ast *ast, t_mini *lash)
{
	char	*path;
	pid_t	pid;

	if (!ast->args[0] || !ast->args[0][0])
	{
		ft_putstr_fd("Command '' not found\n", 2);
		lash->exit_code = 127;
		return ;
	}
	path = get_exec_path(ast, lash);
	if (!path)
		return ;
	pid = fork();
	if (pid == -1)
	{
		perror("lash: fork");
		lash->exit_code = errno;
		return ;
	}
	if (pid == 0)
		exec_ext_child(lash, path, ast);
	waitpid(pid, &lash->exit_code, 0);
	init_signals(lash);
	handle_sig_int(0);
	handle_exit_status(path, lash);
}
