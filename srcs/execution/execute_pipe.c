#include "../minishell.h"

void	prepare_pipe(t_ast *node, t_mini *lash)
{
	set_fd = STDOUT_FILENO;
	if ()
		set_fd = STDIN_FILENO;
	if (dup2(fds[which one], set_fd) == -1)
	{
		close fds
		perror("lash: pipe dup2");
		exit(lash->exit_code);
	}
}

void	go_right(t_ast *node, t_mini *lash, int fds, int *pid)
{
	if (pid = fork() == -1)
		error
	if (pid == 0)
	{
		prepare_pipe(fds, lash, fd stuff);
		close(fd[0]);
		begin_execution(node, stuff);
		close(fd[1]);
	}
	lash->exit_code = 0;
}

void	go_left(t_ast *node, t_mini *lash, int *fds, int *pid)
{
	if (pid = fork() == -1)
		error
	if (pid == 0)
	{
		prepare_pipe(fds, lash, fd stuff);
		close(fd[1]);
		begin_execution(node, whatever);
		close(fd[0]);
	}
	lash->exit_code = 0;
}

void	execute_pipe(t_ast *root, t_mini *lash)
{
	int	fds[2]; //fds[0] = read end, fds[1] = write end
	int	left_pid;
	int	right_pid;

	left_pid = 0;
	right_pid = 0;
	if (pipe(fds) == -1)
		error
	lash.pipe_read = fds[0];
	lash.pipe_write = fds[1];
	go_left(root->left, lash, fds, &left_pid);
	close(fds[1]);
	go_right(root->right, lash, fds, &right_pid);
	close(fds[0]);
	waitpid(left_pid);
	waitpid(right_pid);
}
