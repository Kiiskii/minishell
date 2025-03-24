#include <readline/readline.h>
#include <readline/history.h>
#include "../minishell.h"

void	start_readline(t_envi *env)
{
	char	*input;
	t_token	*tokens;
	t_token	*tmp;

	tokens = NULL;
	while (1)
	{
		input = readline("lash$: ");
		tokenize_input(input, &tokens);
		begin_execution(input, env);
		tmp = tokens;
		while (tmp)
		{
			printf("Token: %s, Type: %d\n", tmp->token, tmp->type);
			tmp = tmp->next;
		}
		tokens = NULL;
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
	start_readline(envi);
	printf("\nExiting lash...\n");
	// implement signalhandling
	return (0);
}
