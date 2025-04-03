#include "../minishell.h"

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
	//char	**cmd_args;

	branch = NULL;
	tmp = list;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type >= REDIR_IN && tmp->type <= REDIR_APP)
		{
			branch = create_redir(tmp->type, tmp->next->token, branch);
			//cmd_args = create_args(list);
			//branch->left = build_cmd(cmd_args);
			tmp = tmp->next->next;
			list = tmp;
		}
		else
			tmp = tmp->next;
	}
	return (branch);
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
	new_node->filename = NULL;
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
