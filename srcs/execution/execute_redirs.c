#include "../minishell.h"

//TO DO: test with > out1.txt > out2.txt echo which one will this > out3.txt go to
//TO DO: figure out all error codes and wether strerror gives correct error messages
//TODO: when does opening fail in out and append?
//TODO: get fds from lash struct instead?

void	redirect_append(t_ast *head, t_mini *lash)
{
	int	fd;

	fd = open(head->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("lash: redirect_append: ", 2);
		perror(head->filename);
		lash->exit_code = 1;
		return ; //or exit?
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		perror("lash: dup2"); //TODO: make sure other dup2s handle errors like this
		lash->exit_code = errno;
		exit(lash->exit_code);
	}
	close(fd);
}

void	redirect_out(t_ast *head, t_mini *lash)
{
	int	fd;

	fd = open(head->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644); //-rw-r--r--
	if (fd == -1)
	{
		ft_putstr_fd("lash: redirect_out: ", 2);
		perror(head->filename);
		lash->exit_code = 1;
		return ; //exit(lash->exit_code);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		perror("lash: dup2");
		lash->exit_code = errno;
		exit(lash->exit_code);
	}
	close(fd);
}

void	redirect_in(t_ast *node, t_mini *lash)
{
	int	fd;

	fd = open(node->filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("lash: ", 2); //TODO: use perror?
		ft_putstr_fd(node->filename, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		lash->exit_code = 1;
		exit(lash->exit_code); //exit here, as we are inside child? close fd?
	}
	if (dup2(fd, STDIN_FILENO) == -1) //error check
	{
		close(fd);
		perror("lash: dup2");
		lash->exit_code = errno;
		exit(lash->exit_code);
	}
	close(fd);
}

void	execute_redirs(t_ast *node, t_mini *lash)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (node->type == REDIR_IN)
			redirect_in(node, lash);
		else if (node->type == REDIR_OUT)
			redirect_out(node, lash);
		else if (node->type == REDIR_APP)
			redirect_append(node, lash);
//		else
//			heredoc
		if (lash->exit_code == 0)
			begin_execution(node->left, lash);
		if (lash->exit_code == 0)
			begin_execution(node->right, lash);
		exit(lash->exit_code);
	}
	waitpid(pid, &lash->exit_code, 0);
}
