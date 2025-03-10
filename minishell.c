#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

int	main()
{
	t_command input;

	ft_memset(&input, 0, sizeof(t_command));
	while (1)
	{
		input.command = readline("lash$: ");
		if (!input.command)
		{
			ft_printf("\nExiting lash...\n");
			break ;
		}
		free(input.command);
	}
	return (0);
}
