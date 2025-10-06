/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillen <lguillen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:41:43 by lguillen          #+#    #+#             */
/*   Updated: 2025/05/19 10:41:44 by lguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ast	*add_node_left(t_ast *node, t_ast *new_node)
{
	t_ast	*tmp;

	if (!node)
		return (new_node);
	else
	{
		tmp = node;
		while (tmp->left)
			tmp = tmp->left;
		tmp->left = new_node;
	}
	return (node);
}

t_ast	*add_node_right(t_ast *node, t_ast *new_node)
{
	t_ast	*tmp;

	if (!node)
		return (new_node);
	else
	{
		tmp = node;
		while (tmp->right)
			tmp = tmp->right;
		tmp->right = new_node;
	}
	return (node);
}
