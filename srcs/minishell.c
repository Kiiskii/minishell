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
			t_ast *tmp2 = tmp->right;
			while (tmp2)
			{
				printf("Type: %d, Filename: %s\n", tmp2->type, tmp2->filename);
				tmp2 = tmp2->right;
			}
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

//TODO: Basic version of creating right tree working. For some reason it's building it the wrong way, need to that. Next up also  is to create left command nodes for redirs. Lastly need to handle when redirs or pipes dont exist.
