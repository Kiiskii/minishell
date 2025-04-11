#include "../minishell.h"

t_ast	*create_args(char **args, t_ast *branch)
{
	t_ast	*new_node;
	t_ast	*tmp;

	new_node = malloc(sizeof(t_ast));
	//malloc check
	new_node->type = WORD;
	new_node->filename = NULL;
	new_node->args = args;
	new_node->left = NULL;
	new_node->right = NULL;
	if (!branch)
		return (new_node);
	else
	{
		tmp = branch;
		while (tmp->right)
			tmp = tmp->right;
		tmp->right = new_node;
	}
	return (branch);
}

t_ast	*create_redir(t_token_type redir, char *filename, t_ast *branch)
{
	t_ast	*new_node;
	t_ast	*tmp;

	new_node = malloc(sizeof(t_ast));
	/*
	 malloc check
	*/
	new_node->type = redir;
	new_node->filename = filename;
	new_node->args = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	if (!branch)
		return (new_node);
	else
	{
		tmp = branch;
		while (tmp->right)
			tmp = tmp->right;
		tmp->right = new_node;
	}
	return (branch);
}

t_ast	*build_right(t_token *list)
{
	t_token *tmp;
	t_ast	*branch;
	char	**cmd_args;

	branch = NULL;
	tmp = list;
	if (tmp->type == PIPE)
		tmp = tmp->next;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type >= REDIR_IN && tmp->type <= REDIR_APP)
		{
			branch = create_redir(tmp->type, tmp->next->token, branch);
			tmp = tmp->next->next;
		}
		else
			tmp = tmp->next;
	}
	cmd_args = list_to_array(list);
	if (!cmd_args)
		return (NULL);
	branch = create_args(cmd_args, branch);
	return (branch);
}

t_ast	*create_tree(t_ast *tree, t_token *list, t_token_type type)
{
	t_ast	*new_node;
	t_ast	*tmp;

	new_node = malloc(sizeof(t_ast));
	 //malloc check
	if (type == PIPE)
	{
		new_node->type = type;
		new_node->filename = NULL;
		new_node->args = NULL;
		new_node->left = NULL;
		new_node->right = build_right(list);
	}
	else
		new_node = build_right(list);
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
	if (list->type == PIPE)
		tmp = list->next;
	else
		tmp = list;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			tree = build_ast(tmp);
			break ;
		}
		tmp = tmp->next;
	}
	tree = create_tree(tree, list, list->type);
	return (tree);
}
