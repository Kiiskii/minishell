#include "../minishell.h"

void	free_tokens(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	while (list)
	{
		list = list->next;
		free(tmp->token);
		free(tmp);
		tmp = list;
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
