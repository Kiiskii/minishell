#include "../minishell.h"

int	create_temp_file(t_ast *leaf, char **filename, int error, t_mini *lash)
{
	error = create_unique_filename(filename);
	if (error != 0)
		return (error);
	leaf->fd = open(*filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (leaf->fd == -1)
	{
		ft_putstr_fd("lash: ", 2);
		perror(leaf->filename);
		lash->exit_code = 1;
		return (-1);
	}
	return (0);
}

char	*expand_heredoc(char *line, t_mini *lash)
{
	t_indexer	s;
	char		*newline;

	ft_memset(&s, 0, sizeof(t_indexer));
	s.str = line;
	newline = ft_strdup("");
	while (s.str[s.i])
	{
		if (s.str[s.i] == '$')
			newline = handle_exps(&s, lash, newline);
		s.i++;
	}
	if (s.j < s.i)
		newline = wrap_join(newline, ft_substr(s.str, s.j, s.i - s.j));
	free(line);
	return (newline);
}

int	handle_heredoc(t_ast *leaf, int dont_expand, t_mini *lash, int error)
{
	char	*filename;
	int		heredoc_stdin;

	filename = NULL;
	error = create_temp_file(leaf, &filename, error, lash);
	if (error != 0)
		return (error);
	init_signals_heredoc();
	heredoc_stdin = dup(STDIN_FILENO);
	if (heredoc_stdin == -1)
	{
		perror("lash: dup2");
		lash->exit_code = errno;
		return (-1);
	}
	if (heredoc_stdin == -1)
		return (-1);
	error = heredoc_readline_loop(leaf, lash, heredoc_stdin, dont_expand);
	if (g_signum != SIGINT)
		heredoc_cleanup(leaf, heredoc_stdin, filename);
	else
		destroy_filename(filename);
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

int	iterate_heredoc(t_ast *tree, t_mini *lash, int error)
{
	t_ast	*tmp;

	tmp = tree;
	if (error != 0)
		return (error);
	if (!tmp)
		return (error);
	if (tmp->type == HEREDOC)
		error = iterate_branch_right(tmp, lash, error);
	if (error != 0)
		return (error);
	error = iterate_heredoc(tmp->left, lash, error);
	if (error != 0)
		return (error);
	error = iterate_branch_right(tmp->right, lash, error);
	return (error);
}
