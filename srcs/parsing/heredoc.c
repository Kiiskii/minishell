#include "../minishell.h"

char	*create_unique_filename(void)
{
	char	*filename;
	char	*num;
	int		i;

	i = 0;
	while (1)
	{
		num = ft_itoa(i);
		if (!num)
			return (NULL);
		filename = ft_strjoin("heredoc_temp_", num);
		free(num);
		if (!filename)
			return (NULL);
		if (access(filename, F_OK) != 0)
			return (filename);
		free(filename);
		i++;
	}
}

char	*create_temp_file(t_ast *leaf)
{
	char	*filename;

	filename = create_unique_filename();
	if (!filename)
		return (NULL);
	leaf->fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (leaf->fd == -1)
		return (NULL);
	return (filename);
}

void	handle_heredoc(t_ast *leaf)
{
	char	*line;
	char	*filename;

	filename = create_temp_file(leaf);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!(ft_strcmp(line, leaf->filename)))
			break ;
		ft_putstr_fd(line, leaf->fd);
		write(leaf->fd, "\n", 1);
		free(line);
		//malloc fail
	}
	free(line);
	free(leaf->filename);
	leaf->filename = filename;
	leaf->type = REDIR_IN;
}

void	iterate_branch_right(t_ast *branch)
{
	t_ast	*tmp;

	tmp = branch;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			handle_heredoc(tmp);
		tmp = tmp->right;
	}
}

void	iterate_heredoc(t_ast *tree)
{
	t_ast	*tmp;

	tmp = tree;
	if (!tmp)
		return ;
	if (tmp->type == HEREDOC)
		iterate_branch_right(tmp);
	iterate_heredoc(tmp->left);
	iterate_branch_right(tmp->right);
}
