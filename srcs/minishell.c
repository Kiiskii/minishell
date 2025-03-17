#include <readline/readline.h>
#include <readline/history.h>
#include "../minishell.h"

void	start_readline()
{
	char	*input;
	t_token	*tokens;

	tokens = NULL;
	while (1)
	{
		input = readline("lash$: ");
		tokenize_input(input, &tokens);
		free(input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_envi	*envi;

	if (argc != 1)
		return (1);
	(void)argv;
	envi = NULL;
	env_to_list(&envi, env);
	start_readline();
	printf("\nExiting lash...\n");
	// implement signalhandling
	return (0);
}
