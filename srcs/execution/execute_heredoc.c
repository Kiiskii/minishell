#include "../minishell.h"

void  execute_heredoc(t_ast *node, t_mini *lash)
{
	char	*input;

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
	free(input);
}
