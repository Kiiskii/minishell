#include "../minishell.h"

t_ast	build_right(t_token *list)
{
	t_token *tmp;
	t_ast	*branch;

	tmp = list;
	while (tmp)
	{
		if (tmp->next->type == REDIR_OUT)
			branch = create_redir();
		else if (tmp->type == REDIR_IN)
			branch = create_redir();
		else if (tmp->type == PIPE)
			return (branch); ?
		else
			tmp = tmp->next;
	}
}

t_ast	*create_tree(t_ast *tree, t_token *list)
{
	t_ast	*new_node;
	t_ast	*tmp;

	new_node = malloc(sizeof(t_ast));
	/*
	 malloc check
	*/
	new_node->type = PIPE;
	new_node->filename = list->token;
	new_node->args = NULL;
	new_node->left = NULL;
	list = list->next;
	new_node->right = build_right(list);
	if (!tree)
		return (new_node);
	else
	{
		tmp = tree;
		while (tmp->left)
			tmp = tmp->left;
		tmp->left = new_node;
	}
	return (tree);
}

t_ast	*build_ast(t_token *list)
{
	t_token	*tmp;
	t_ast	*tree;

	tree = NULL;
	tmp = list;
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			tree = build_ast(tmp);
			printf("token = %s\n", tmp->next->token);
			break ;
		}
		tmp = tmp->next;
	}
	tree = create_tree(tree, list);
	return (tree);
}
