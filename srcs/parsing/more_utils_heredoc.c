#include "../minishell.h"

void	write_heredoc(char **line, int fd)
{
	ft_putstr_fd(*line, fd);
	write(fd, "\n", 1);
	free(*line);
}

int	remove_delim_quotes(t_ast *node)
{
	char	*new_filename;
	int		len;

	len = 0;
	len = count_delim_len(node->filename);
	new_filename = malloc(len + 1);
	if (!new_filename)
		return (-2);
	heredoc_rm_quotes(node->filename, new_filename);
	free(node->filename);
	node->filename = new_filename;
	return (0);
}

int	heredoc_readline_loop(t_ast *leaf, t_mini *lash, int fd, int dont_expand)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_signum == SIGINT)
		{
			signal_exit_heredoc(line, lash, fd, leaf);
			break ;
		}
		if (!line || !(ft_strcmp(line, leaf->filename)))
			break ;
		if (dont_expand == 0 && ft_strchr(line, '$') != NULL)
			line = expand_heredoc(line, lash);
		if (line && line[0] == '\0')
		{
			free(line);
			line = ft_strdup("");
		}
		if (!line)
			return (-2);
		write_heredoc(&line, leaf->fd);
	}
	free(line);
	return (0);
}
