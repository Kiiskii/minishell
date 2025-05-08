#include "../minishell.h"

void	malloc_fail_message(t_token **tokens)
{
	free_tokens(tokens);
	tokens = NULL;
	ft_putstr_fd("Cannot allocate memory, please CTRL + D!\n", 2);
}

void	malloc_fail_message_tree(t_ast *tree)
{
	free_ast(tree);
	tree = NULL;
	ft_putstr_fd("Cannot allocate memory, please CTRL + D!\n", 2);
}

void	free_tokens(t_token **list)
{
	t_token	*current;
	t_token	*next;

	if (!list || !(*list))
		return ;
	current = *list;
	while (current)
	{
		next = current->next;
		if (current->token)
			free(current->token);
		free(current);
		current = next;
	}
	*list = NULL;
}

void	free_env(t_envi *env)
{
	t_envi	*tmp;

	tmp = env;
	while (env)
	{
		env = env->next;
		free(tmp->value);
		free(tmp->key);
		free(tmp);
		tmp = env;
	}
}

void	free_ast(t_ast *tree)
{
	if (!tree)
		return ;
	free_ast(tree->left);
	free_ast(tree->right);
	if (tree->fd != -1)
	{
		unlink(tree->filename);
		close(tree->fd);
	}
	if (tree->filename)
		free(tree->filename);
	//if (tree->args)
	//	free_arr(tree->args);
	free(tree);
}
