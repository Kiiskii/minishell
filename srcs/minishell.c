#include <readline/readline.h>
#include <readline/history.h>
#include "../minishell.h"

void	start_readline(char **argv, t_envi *env)
{
	char	*input;
	t_token	*tokens;

	tokens = NULL;
	while (1)
	{
		input = readline("lash$: ");
		tokenize_input(input, &tokens);
		begin_execution(argv, env);
		free(input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_envi	*envi;

	if (argc != 1)
		return (1);
//	(void)argv;
	envi = NULL;
	env_to_list(&envi, env);
	start_readline(argv, envi);
	printf("\nExiting lash...\n");
	// implement signalhandling
	return (0);
}
