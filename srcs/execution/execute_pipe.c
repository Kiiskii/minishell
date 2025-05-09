#include "../minishell.h"

static void	go_right(t_ast *node, t_mini *lash, int *fds, int *pid)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror("lash: fork\n");
		lash->exit_code = errno;
		return ;
	}
	if (*pid == 0)
	{
		close(lash->fd_in);
		reset_default_signals();
		close(fds[1]);
		if (dup2(fds[0], STDIN_FILENO) == -1)
		{
			close(fds[0]);
			perror("lash: dup2");
			lash->exit_code = errno;
			exit(errno);
		}
		close(fds[0]);
		begin_execution(node, lash);
		exit_process(lash);
	}
}

static void	go_left(t_ast *node, t_mini *lash, int *fds, int *pid)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror("lash: fork");
		lash->exit_code = errno;
		return ;
	}
	if (*pid == 0)
	{
		reset_default_signals();
		close(fds[0]);
		if (dup2(fds[1], STDOUT_FILENO) == -1)
		{
			close(fds[1]);
			perror("lash: dup2");
			lash->exit_code = errno;
			exit_process(lash);
		}
		close(fds[1]);
		begin_execution(node, lash);
		close(lash->fd_in);
		exit_process(lash);
	}
}

void	execute_pipe(t_ast *node, t_mini *lash)
{
	int	fds[2];
	int	left_pid;
	int	right_pid;

	if (pipe(fds) == -1)
	{
		perror("lash: pipe");
		lash->exit_code = errno;
		return ;
	}
	go_left(node->left, lash, fds, &left_pid);
	close(fds[1]);
	go_right(node->right, lash, fds, &right_pid);
	close(fds[0]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &lash->exit_code, 0);
	if (WIFEXITED(lash->exit_code))
		lash->exit_code = WEXITSTATUS(lash->exit_code);
}
