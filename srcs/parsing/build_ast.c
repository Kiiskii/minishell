#include "../minishell.h"

t_ast	*create_args(char **args, t_ast *branch)
{
	t_ast	*new_node;

	new_node = ft_calloc(1, sizeof(t_ast));
	if (!new_node)
	{
		free_ast(branch);
		free_arr(args);
		return (NULL);
	}
	new_node->type = WORD;
	new_node->filename = NULL;
	new_node->args = args;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->fd = -1;
	branch = add_node_right(branch, new_node);
	return (branch);
}

t_ast	*create_redir(t_token_type redir, char *filename, t_ast *branch)
{
	t_ast	*new_node;

	new_node = ft_calloc(1, sizeof(t_ast));
	if (!new_node)
	{
		free_ast(branch);
		return (NULL);
	}
	new_node->type = redir;
	new_node->filename = ft_strdup(filename);
	if (!new_node->filename)
	{
		free(new_node);
		free_ast(branch);
		return (NULL);
	}
	new_node->args = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->fd = -1;
	branch = add_node_right(branch, new_node);
	return (branch);
}

t_ast	*build_right(t_token *list)
{
	t_token	*tmp;
	t_ast	*branch;

	branch = NULL;
	tmp = list;
	if (tmp->type == PIPE)
		tmp = tmp->next;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type >= REDIR_IN && tmp->type <= REDIR_APP)
		{
			branch = create_redir(tmp->type, tmp->next->token, branch);
			if (!branch)
				return (NULL);
			tmp = tmp->next->next;
		}
		else
			tmp = tmp->next;
	}
	branch = handle_arguments(list, branch);
	return (branch);
}

t_ast	*create_tree(t_ast *tree, t_token *list, t_token_type type, int *error)
{
	t_ast	*new_node;

	if (type == PIPE)
	{
		ft_memset(&new_node, 0, sizeof(t_ast *));
		new_node = ft_calloc(1, sizeof(t_ast));
		if (!new_node)
		{
			free_ast(tree);
			*error = 1;
			return (NULL);
		}
		new_node->type = type;
		new_node->right = build_right(list);
	}
	else
		new_node = build_right(list);
	if (!new_node)
	{
		free_ast(tree);
		return (NULL);
	}
	tree = add_node_left(tree, new_node);
	return (tree);
}

t_ast	*build_ast(t_token **list, int *error)
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
			tree = build_ast(&tmp, error);
			break ;
		}
		tmp = tmp->next;
	}
	tree = create_tree(tree, *list, (*list)->type, error);
	if (*error != 0)
	{
		free_ast(tree);
		return (NULL);
	}
	if (!tree)
		return (NULL);
	return (tree);
}
