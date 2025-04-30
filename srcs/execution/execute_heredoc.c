#include "../minishell.h"

void  execute_heredoc(t_ast *node, t_mini *lash) //or preprocess_heredoc
{
	char	*input;
	char	*name;
	int 	fd;

	name = create_filename();
	fd = open(name, O_CREAT | O_RDWR | O_EXCL, 0644);
	while (1)
	{
		input = readline(">");
		if (!input)
			return ;
		if (ft_strcmp(input, node->filename) == 0)
			break ;
		else
			write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	close(fd);
	//signal handler
	//fd = open(name, O_RDWR, 0644); don't do because done in redir in
	free(input);
}
