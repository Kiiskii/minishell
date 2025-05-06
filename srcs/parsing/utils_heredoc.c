#include "../minishell.h"

void	signal_exit_heredoc(char *line, t_mini *lash, int fd)
{
	free(line);
	line = NULL;
	lash->exit_code = 130;
	close(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	heredoc_cleanup(t_ast *leaf, char *line, int fd, char *filename)
{
	free(line);
	line = NULL;
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

char	*heredoc_rm_quotes(t_ast *node)
{
	char	*new_filename;
	int		i;
	int		j;
	int		len;

	len = count_delim_len(node->filename);
	i = 0;
	j = 0;
	new_filename = malloc(len + 1);
	while (node->filename[i])
	{
		if (node->filename[i] != '"' && node->filename[i] != '\'')
		{
			new_filename[j] = node->filename[i];
			j++;
		}
		i++;
	}
	new_filename[j] = '\0';
	return (new_filename);
}

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
