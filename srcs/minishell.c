#include <readline/readline.h>
#include <readline/history.h>
#include "../minishell.h"

void	start_readline()
{
	char	*input;
	t_token	*tokens;
	t_token	*tmp;

	tokens = NULL;
	while (1)
	{
		input = readline("lash$: ");
		if (!input)
		{
			printf("\nExiting lash...\n");
			break ;
		}
		tokenize_input(input, &tokens);
		tmp = tokens;
		while (tmp)
		{
			printf("Token: %s, Type: %d\n", tmp->token, tmp->type);
			tmp = tmp->next;
		}
		free(input);
	}
}

int	main()
{
	start_readline();
	return (0);
}
