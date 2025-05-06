#include "../minishell.h"

//TODO: INPUT MAX LEN, NEW VALUE IN HEADERFILE!
// LS & RM ADD A NEWLINE

/*
void	print_args(char **args)
{
	int	i = 0;

	while (args[i])
	{
		printf("%s ", args[i]);
		i++;
	}
}

void	print_ast(t_ast *tree)
{
	t_ast	*tmp;

	while (tree)
	{
		tmp = tree;
		if (tmp->type == PIPE)
			printf("PIPE -- ");
		else if (tmp->type >= REDIR_IN && tmp->type <= REDIR_APP)
			printf("%s -- ", tmp->filename);
		else
			print_args(tmp->args);
		if (tmp->right)
		{
			tmp = tmp->right;
			while (tmp)
			{
				if (tmp->type >= REDIR_IN && tmp->type <= REDIR_APP)
					printf("%s -- ", tmp->filename);
				else
					print_args(tmp->args);
				tmp = tmp->right;
			}
		}
		tree = tree->left;
		printf("\n");
	}
}

void	print_tokens(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		printf("%s %d - ", tmp->token, tmp->type);
		tmp = tmp->next;
	}
	printf("\n");
}
*/

sig_atomic_t	g_signum = 0;

int	begin_tokenizing(t_token **tokens, t_mini *lash, char *input)
{
	tokenize_input(input, tokens);
	if (!tokens)
		return (0);
	if (error_iterate_list(*tokens, lash) == 0)
		return (0);
	expand_tokens(tokens, lash);
	//re_tokenize(tokens);
	remove_quotes(tokens);
	if (!tokens || !*tokens)
		return (0);
	//print_tokens(*tokens);
	return (1);
}

int	begin_ast_heredoc(t_token **tokens, t_mini *lash)
{
	t_ast	*tree;

	tree = build_ast(tokens);
	if (!tree)
	{
		malloc_fail_message_tree(tree);
		return (0);
	}
	free_tokens(tokens);
	//print_ast(tree);
	iterate_heredoc(tree, lash);
	if (g_signum != SIGINT)
		begin_execution(tree, lash);
	free_ast(tree);
	return (1);
}

void	start_readline(t_mini *lash, int fd)
{
	char	*input;
	t_token	*tokens;

	while (1)
	{
		init_signals();
		dup2(fd, STDIN_FILENO);
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
	}
}

int	main(int argc, char **argv, char **env)
{
	t_envi	*envi;
	t_mini	lash;
	int		original_stdin;

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
	original_stdin = dup(STDIN_FILENO);
	start_readline(&lash, original_stdin);
	close(original_stdin);
	printf("Exiting lash...\n");
	// implement signalhandling
	return (lash.exit_code);
}
