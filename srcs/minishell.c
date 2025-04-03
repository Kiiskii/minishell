#include <readline/readline.h>
#include <readline/history.h>
#include "../minishell.h"

void	start_readline(t_mini *lash)
{
	char	*input;
	t_token	*tokens;

	tokens = NULL;
	while (1)
	{
		input = readline("lash$: ");
		tokenize_input(input, &tokens);
		begin_execution(input, lash);
		free(input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_envi	*envi;
	t_mini	lash;

	if (argc != 1)
		return (1);
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
	return (0);
}
