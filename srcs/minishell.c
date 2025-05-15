#include "../minishell.h"

sig_atomic_t	g_signum = 0;

int	begin_tokenizing(t_token **tokens, t_mini *lash, char *input)
{
	tokenize_input(input, tokens);
	if (!tokens)
		return (0);
	expand_tokens(tokens, lash);
	remove_quotes(tokens);
	if (!tokens || !*tokens)
		return (0);
	if (error_iterate_list(*tokens, lash) == 0)
	{
		free_tokens(tokens);
		return (0);
	}
	return (1);
}

int	begin_ast_heredoc(t_token **tokens, t_mini *lash)
{
	t_ast	*tree;
	int		error;

	tree = build_ast(tokens);
	if (!tree)
	{
		malloc_fail_message_tree(tree);
		return (0);
	}
	free_tokens(tokens);
	error = iterate_heredoc(tree, lash, 0);
	if (error == -2)
	{
		malloc_fail_message_tree(tree);
		return (0);
	}
	else if (error == -1)
		return (0);
	lash->head = tree;
	if (g_signum == 0)
		begin_execution(tree, lash);
	delete_heredoc_temps(tree);
	free_ast(tree);
	return (1);
}

void	start_readline(t_mini *lash)
{
	char	*input;
	t_token	*tokens;

	while (1)
	{
		init_signals();
		dup2(lash->fd_in, STDIN_FILENO);
		tokens = NULL;
		input = readline("lash$: ");
		if (!input)
			break ;
		if (input[0] == '\0' || error_input(input, lash) == 0)
		{
			free(input);
			continue ;
		}
		add_history(input);
		if (begin_tokenizing(&tokens, lash, input) == 0)
			continue ;
		if (begin_ast_heredoc(&tokens, lash) == 0)
			continue ;
		free(input);
		g_signum = 0;
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
	if (!envi)
	{
		ft_putstr_fd("Cannot allocate memory for env!\n", 2);
		return (1);
	}
	ft_memset(&lash, 0, sizeof(t_mini));
	lash.env = envi;
	lash.exit_code = 0;
	lash.fd_in = -1;
	lash.fd_in = dup(STDIN_FILENO);
	if (lash.fd_in == -1)
		exit(1);
	start_readline(&lash);
	close(lash.fd_in);
	free_env(lash.env);
	printf("Exiting lash...\n");
	return (lash.exit_code);
}
