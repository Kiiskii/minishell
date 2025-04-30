#include "../minishell.h"

void	malloc_fail_message(t_token **tokens)
{
	free_tokens(tokens);
	tokens = NULL;
	ft_putstr_fd("Cannot allocate memory, please CTRL + D!\n", 2);
}

void	free_tokens(t_token **list)
{
	t_token	*tmp;

	tmp = *list;
	while (tmp)
	{
		tmp = tmp->next;
		if ((*list)->token)
			free((*list)->token);
		if (*list)
			free(*list);
		*list = tmp;
	}
}

void	free_ast(t_ast *tree)
{
	if (!tree)
		return ;
	free_ast(tree->left);
	free_ast(tree->right);
	if (tree->filename)
		free(tree->filename);
	if (tree->args)
		free_arr(tree->args);
	free(tree);
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

void    free_ast(t_ast *tree)
{
    if (!tree)
        return ;
    free_ast(tree->left);
    free_ast(tree->right);
    if (tree->filename)
        free(tree->filename);
    if (tree->args)
        free_arr(tree->args);
    free(tree);
}
