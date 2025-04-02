#include <readline/readline.h>
#include <readline/history.h>
#include "../minishell.h"

void	start_readline(t_envi *env)
{
	char	*input;
	t_token	*tokens;
	t_ast	*tmp;
	t_ast	*tree;

	tokens = NULL;
	while (1)
	{
		input = readline("lash$: ");
		tokenize_input(input, &tokens);
		tree = build_ast(tokens);
		begin_execution(input, env);
		tmp = tree;
		int nodecount = 0;
		while (tmp)
		{
			nodecount++;
			printf("Type: %d\n", tmp->type);
			tmp = tmp->left;
		}
		printf("Nodecount = %d\n", nodecount);
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

//TODO: Finalize right side branches. Figure out how to get correct commands to correct redirs left.
