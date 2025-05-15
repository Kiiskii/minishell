#include "../minishell.h"

void	signal_exit_heredoc(char *line, t_mini *lash, int fd, t_ast *leaf)
{
	free(line);
	line = NULL;
	lash->exit_code = 130;
	close(leaf->fd);
	leaf->fd = -1;
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	heredoc_cleanup(t_ast *leaf, int fd, char *filename)
{
	close(leaf->fd);
	free(leaf->filename);
	leaf->filename = NULL;
	leaf->filename = filename;
	leaf->type = REDIR_IN;
	close(fd);
}

int	count_delim_len(char *filename)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (filename[i])
	{
		if (filename[i] != '"' && filename[i] != '\'')
			len++;
		i++;
	}
	return (len);
}

void	heredoc_rm_quotes(char *filename, char *new_filename)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (filename[i])
	{
		if (filename[i] != '"' && filename[i] != '\'')
		{
			new_filename[j] = filename[i];
			j++;
		}
		i++;
	}
	new_filename[j] = '\0';
}

int	create_unique_filename(char **filename)
{
	char	*num;
	int		i;

	i = 0;
	while (1)
	{
		num = ft_itoa(i);
		if (!num)
			return (-2);
		*filename = ft_strjoin("heredoc_temp_", num);
		free(num);
		if (!*filename)
			return (-2);
		if (access(*filename, F_OK) != 0)
			return (0);
		free(*filename);
		i++;
	}
}
