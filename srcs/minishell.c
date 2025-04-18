#include <readline/readline.h>
#include <readline/history.h>
#include "../minishell.h"

void	start_readline(t_mini *lash)
{
	char	*input;
	t_token	*tokens;
	t_ast	*tree;

	tokens = NULL;
	while (1)
	{
		input = readline("lash$: ");
		add_history(input);
		tokenize_input(input, &tokens);
		free(input);
		if (!tokens)
			continue ;
		tree = build_ast(tokens);
		begin_execution(tree, lash);
		free_tokens(tokens);
		tokens = NULL;
	}
	tokens = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_envi	*envi;
	t_mini	lash;

	if (argc != 1)
		return (1); //exit with 1?
	(void)argv;
	envi = NULL;
	env_to_list(&envi, env);
	ft_memset(&lash, 0, sizeof(t_mini));
	lash.env = envi;
	lash.exit_code = 0;
	lash.fd_out = -1;
	lash.fd_in = -1;
	start_readline(&lash);
	printf("\nExiting lash...\n");
	// implement signalhandling
	return (0); //exit with lash->exit_code instead
}
