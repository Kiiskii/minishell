#include "../minishell.h"

static void	redirect_append(t_ast *head, t_mini *lash)
{
	int	fd;

	fd = open(head->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("lash: redirect_append: ", 2);
		perror(head->filename);
		lash->exit_code = 1;
		exit_process(lash);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		perror("lash: dup2");
		lash->exit_code = errno;
		exit_process(lash);
	}
	close(fd);
}

static void	redirect_out(t_ast *head, t_mini *lash)
{
	int	fd;

	fd = open(head->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("lash: redirect_out: ", 2);
		perror(head->filename);
		lash->exit_code = 1;
		exit_process(lash);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		perror("lash: dup2");
		lash->exit_code = errno;
		exit_process(lash);
	}
	close(fd);
}

static void	redirect_in(t_ast *node, t_mini *lash)
{
	int	fd;

	fd = open(node->filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("lash: ", 2);
		perror(node->filename);
		lash->exit_code = 1;
		exit_process(lash);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		perror("lash: dup2");
		lash->exit_code = errno;
		exit_process(lash);
	}
	close(fd);
}

static void	check_redir_type(t_ast *node, t_mini *lash)
{
	if (node->type == REDIR_IN)
		redirect_in(node, lash);
	else if (node->type == REDIR_OUT)
		redirect_out(node, lash);
	else if (node->type == REDIR_APP)
		redirect_append(node, lash);
}

void	execute_redirs(t_ast *node, t_mini *lash)
{
	pid_t	pid;

	sig_ignore();
	pid = fork();
	if (pid == -1)
	{
		perror("lash: fork");
		lash->exit_code = errno;
		return ;
	}
	if (pid == 0)
	{
		lash->exit_code = 0;
		reset_default_signals();
		check_redir_type(node, lash);
		if (lash->exit_code == 0 && node->left)
			begin_execution(node->left, lash);
		if (lash->exit_code == 0 && node->right)
			begin_execution(node->right, lash);
		close(lash->fd_in);
		exit_process(lash);
	}
	wait_child(pid, lash);
}
