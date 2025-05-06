#include "../minishell.h"

int	create_temp_file(t_ast *leaf, char **filename, int error)
{
	error = create_unique_filename(filename);
	if (error != 0)
		return (error);
	leaf->fd = open(*filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (leaf->fd == -1)
		return (-1);
	return (0);
}

char	*expand_heredoc(char *line, t_mini *lash)
{
	t_indexer	s;
	char		*newline;

	ft_memset(&s, 0, sizeof(t_indexer));
	s.str = line;
	newline = "";
	while (s.str[s.i])
	{
		if (s.str[s.i] == '$')
			newline = handle_exps(&s, lash, newline);
		s.i++;
	}
	if (s.j < s.i)
		newline = ft_strjoin(newline, ft_substr(s.str, s.j, s.i - s.j));
	free(line);
	return (newline);
}

int	handle_heredoc(t_ast *leaf, int dont_expand, t_mini *lash, int error)
{
	char	*line;
	char	*filename;
	int		heredoc_stdin;

	filename = NULL;
	if (create_temp_file(leaf, &filename, error) != 0)
		return (error);
	init_signals_heredoc();
	heredoc_stdin = dup(STDIN_FILENO);
	while (1)
	{
		line = readline("> ");
		if (g_signum == SIGINT)
			signal_exit_heredoc(line, lash, heredoc_stdin);
		if (!line || !(ft_strcmp(line, leaf->filename)))
			break ;
		if (dont_expand == 0 && ft_strchr(line, '$') != NULL)
			line = expand_heredoc(line, lash);
		if (!line)
			return (-2);
		write_heredoc(&line, leaf->fd);
	}
	if (g_signum != SIGINT)
		heredoc_cleanup(leaf, line, heredoc_stdin, filename);
	return (error);
}

int	iterate_branch_right(t_ast *branch, t_mini *lash, int error)
{
	t_ast	*tmp;
	int		dont_expand;

	tmp = branch;
	while (tmp)
	{
		dont_expand = 0;
		if (tmp->type == HEREDOC)
		{
			if (ft_strchr(tmp->filename, '"') != NULL)
				dont_expand = 1;
			else if (ft_strchr(tmp->filename, '\'') != NULL)
				dont_expand = 1;
			if (dont_expand == 1)
				error = remove_delim_quotes(tmp);
			if (error != 0)
				return (error);
			error = handle_heredoc(tmp, dont_expand, lash, error);
			if (error != 0)
				return (error);
		}
		tmp = tmp->right;
	}
	return (error);
}

void	iterate_heredoc(t_ast *tree, t_mini *lash)
{
	t_ast	*tmp;

	tmp = tree;
	if (!tmp)
		return ;
	if (tmp->type == HEREDOC)
		iterate_branch_right(tmp, lash, 0);
	iterate_heredoc(tmp->left, lash);
	iterate_branch_right(tmp->right, lash, 0);
}
