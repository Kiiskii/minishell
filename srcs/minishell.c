#include "../minishell.h"

//TODO: FUCKING REFACTOR

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
		printf("%s --- ", tmp->token);
		tmp = tmp->next;
	}
	printf("\n");
}

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
		expand_tokens(tokens, lash);
		re_tokenize(tokens, lash);
		remove_quotes(tokens, lash);
		print_tokens(tokens);
		tree = build_ast(tokens);
		//print_ast(tree);
		begin_execution(tree, lash);
		free_tokens(tokens);
		free_ast(tree);
		tokens = NULL;
	}
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
