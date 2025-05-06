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
