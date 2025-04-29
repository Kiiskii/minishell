#include "../minishell.h"

//TODO: REFACTOR HANDLE EXPS, GO THROUGH ALL MALLOCS, CHECK RETURNS AND ATTEMPT TO RETURN TO READLINE WITH NULL, FIX INVALID EXPANSIONS, CHECK "" STUFF
//TALK WITH LAURA ABOUTN REDIR EXPANSION HANDLING FOR AMBIGOUS REDIR

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

int	begin_tokenizing(t_token **tokens, t_mini *lash, char *input)
{
	tokenize_input(input, tokens);
	free(input);
	if (!tokens)
		return (0);
	if (error_iterate_list(*tokens, lash) == 0)
		return (0);
	expand_tokens(tokens, lash);
	//re_tokenize(tokens);
	remove_quotes(tokens, lash);
	if (!*tokens)
		return (0);
	print_tokens(*tokens);
	return (1);
}

void	start_readline(t_mini *lash)
{
	char	*input;
	t_token	*tokens;
	t_ast	*tree;

	while (1)
	{
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
		tree = build_ast(&tokens);
		if (!tree)
		{
			free_ast(tree);
			printf("Cannot allocate memory, please CTRL + D!\n");
			continue ;
		}
		//print_ast(tree);
		free_tokens(&tokens);
		begin_execution(tree, lash);
		free_ast(tree);
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
