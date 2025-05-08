#include "../minishell.h"

//TODO: when does opening fail in out and append?
//TODO: get fds from lash struct instead?
//TODO: instead of exit, enter exit process with ast and lash?

void	redirect_append(t_ast *head, t_mini *lash)
{
	int	fd;

	fd = open(head->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("lash: redirect_append: ", 2);
		perror(head->filename);
		lash->exit_code = 1;
		return ;
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

void	redirect_out(t_ast *head, t_mini *lash)
{
	int	fd;

	fd = open(head->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("lash: redirect_out: ", 2);
		perror(head->filename);
		lash->exit_code = 1;
		return ;
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
		ft_putstr_fd("lash: ", 2);
		perror(node->filename);
		lash->exit_code = 1;
		exit(lash->exit_code);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
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

	pid = fork(); //TODO if pid == -1
	if (pid == 0)
	{
		reset_default_signals();
		if (node->type == REDIR_IN)
			redirect_in(node, lash);
		else if (node->type == REDIR_OUT)
			redirect_out(node, lash);
		else if (node->type == REDIR_APP)
			redirect_append(node, lash);
		if (lash->exit_code == 0 && node->left)
			begin_execution(node->left, lash);
		if (lash->exit_code == 0 && node->right)
			begin_execution(node->right, lash);
		exit(lash->exit_code);
	}
		waitpid(pid, &lash->exit_code, 0);
		if (WIFEXITED(lash->exit_code))
			lash->exit_code = WEXITSTATUS(lash->exit_code);
}
