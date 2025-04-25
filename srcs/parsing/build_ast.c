#include "../minishell.h"

t_ast	*create_args(char **args, t_ast *branch)
{
	t_ast	*new_node;

	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->type = WORD;
	new_node->filename = NULL;
	new_node->args = args;
	new_node->left = NULL;
	new_node->right = NULL;
	branch = add_node_right(branch, new_node);
	return (branch);
}

t_ast	*create_redir(t_token_type redir, char *filename, t_ast *branch)
{
	t_ast	*new_node;

	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->type = redir;
	new_node->filename = ft_strdup(filename);
	if (!new_node->filename)
		return (NULL);
	new_node->args = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	branch = add_node_right(branch, new_node);
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

	if (type == PIPE)
	{
		new_node = malloc(sizeof(t_ast));
		if (!new_node)
			return (NULL);
		new_node->type = type;
		new_node->filename = NULL;
		new_node->args = NULL;
		new_node->left = NULL;
		new_node->right = build_right(list);
		if (!new_node->right)
			return (NULL);
	}
	else
		new_node = build_right(list);
	tree = add_node_left(tree, new_node);
	return (tree);
}

t_ast	*build_ast(t_token **list)
{
	t_token	*tmp;
	t_ast	*tree;

	tree = NULL;
	if ((*list)->type == PIPE)
		tmp = (*list)->next;
	else
		tmp = *list;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			tree = build_ast(&tmp);
			break ;
		}
		tmp = tmp->next;
	}
	tree = create_tree(tree, *list, (*list)->type);
	return (tree);
}
