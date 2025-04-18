#include "../minishell.h"

//void	prepare_pipe(t_ast *node, t_mini *lash)
//{
//	set_fd = STDOUT_FILENO;
//	if ()
//		set_fd = STDIN_FILENO;
//	if (dup2(fds[which one], set_fd) == -1)
//	{
//		close fds
//		perror("lash: pipe dup2");
//		exit(lash->exit_code);
//	}
//}

void	go_right(t_ast *node, t_mini *lash, int *fds)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("lash: fork\n");
		exit_code = errno;
		return ;
	}
	if (pid == 0)
	{
		close(fds[1]);
		if (dup2(fds[0], STDIN_FILENO) == -1)
		{
			close(fds[0]);
			perror("lash: dup2\n");
			exit_code = errno;
			exit(errno);
		}
		close(fds[0]);
		begin_execution(node, lash);
		lash->exit_code = 0;
		exit(exit_code);
	}
}

//void	go_right(t_ast *node, t_mini *lash, int fds, int *pid)
//{
//	if (pid = fork() == -1)
//		error
//	if (pid == 0)
//	{
//		prepare_pipe(fds, lash, fd stuff);
//		close(fd[0]);
//		begin_execution(node, stuff);
//		close(fd[1]);
//	}
//	lash->exit_code = 0;
//}

int	go_left(t_ast *node, t_mini *lash, int *fds)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("lash: fork\n");
		exit_code = errno;
		return ;
	}
	if (pid == 0)
	{
		close(fds[0]);
//		if (lash->write_fd != STDIN_FILENO)
//		{
//			dup2(lash->write_fd, STDIN_FILENO);
		if (dup2(fds[1], STDOUT_FILENO) == -1)
		{
			close(fds[1]);
			perror("lash: dup2\n");
			exit_code = errno;
			exit(errno);
		}
		close(fds[1]);
		begin_execution(node, lash);
		lash->exit_code = 0;
		exit(exit_code);
		}
	}

	return (pid);
}

//void	go_left(t_ast *node, t_mini *lash, int *fds, int *pid)
//{
//	if (pid = fork() == -1)
//		error
//	if (pid == 0)
//	{
//		prepare_pipe(fds, lash, fd stuff);
//		close(fd[1]);
//		begin_execution(node, whatever);
//		close(fd[0]);
//	}
//	lash->exit_code = 0;
//}

void	execute_pipe(t_ast *root, t_mini *lash) //need to add input_fd?
{
	int	fds[2]; //fds[0] = read end, fds[1] = write end
	int	left_pid;
	int	right_pid;

//	left_pid = 0;
//	right_pid = 0;
	if (pipe(fds) == -1)
	{
		perror("lash: pipe\n");
		lash->exit_code = errno;
		return ;
	}
//	lash.pipe_read = fds[0];
//	lash.pipe_write = fds[1];
	left_pid = go_left(root->left, lash); //or &left_pid
	close(fds[1]);
	go_right(root->right, lash, fds, &right_pid);
	close(fds[0]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &lash->exit_code, 0);
}
