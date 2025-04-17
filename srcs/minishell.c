#include "../minishell.h"

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

//void	start_readline()
void	start_readline(t_envi *env)
{
	char	*input;
	t_token	*tokens;
	t_ast	*tree;

	tokens = NULL;
	while (1)
	{
		input = readline("lash$: ");
		add_history(input);
		parse_expansions(input, env);
		tokenize_input(input, &tokens);
		free(input);
		if (!tokens)
			continue ;
		tree = build_ast(tokens);
		print_ast(tree);
		//begin_execution(input, env);
		free_tokens(tokens);
		free_ast(tree);
		tokens = NULL;
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
	//if (!envi)
	start_readline(envi);
	//start_readline();
	printf("\nExiting lash...\n");
	// implement signalhandling
	return (0);
}
