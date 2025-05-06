#include "../minishell.h"

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

void	handle_heredoc(t_ast *leaf, int dont_expand, t_mini *lash)
{
	char	*line;
	char	*filename;
	int		heredoc_stdin;

	filename = create_temp_file(leaf);
	init_signals_heredoc();
	heredoc_stdin = dup(STDIN_FILENO);
	while (1)
	{
		line = readline("> ");
		if (g_signum == SIGINT)
			signal_exit_heredoc(line, lash, heredoc_stdin);
		if (!line)
			break ;
		if (!(ft_strcmp(line, leaf->filename)))
			break ;
		if (dont_expand == 0 && ft_strchr(line, '$') != NULL)
			line = expand_heredoc(line, lash);
		ft_putstr_fd(line, leaf->fd);
		write(leaf->fd, "\n", 1);
		free(line);
	}
	if (g_signum != SIGINT)
		heredoc_cleanup(leaf, line, heredoc_stdin, filename);
}

void	iterate_branch_right(t_ast *branch, t_mini *lash)
{
	t_ast	*tmp;
	int		dont_expand;
	char	*new_filename;

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
			{
				new_filename = heredoc_rm_quotes(tmp);
				free(tmp->filename);
				tmp->filename = new_filename;
			}
			handle_heredoc(tmp, dont_expand, lash);
		}
		tmp = tmp->right;
	}
}

void	iterate_heredoc(t_ast *tree, t_mini *lash)
{
	t_ast	*tmp;

	tmp = tree;
	if (!tmp)
		return ;
	if (tmp->type == HEREDOC)
		iterate_branch_right(tmp, lash);
	iterate_heredoc(tmp->left, lash);
	iterate_branch_right(tmp->right, lash);
}
