/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillen <lguillen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:35:51 by lguillen          #+#    #+#             */
/*   Updated: 2025/05/19 10:35:52 by lguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	begin_execution(t_ast *node, t_mini *lash)
{
	if (!node || !lash)
		return ;
	if (node->type == PIPE)
		execute_pipe(node, lash);
	else if (node->type == WORD)
		execute_command(node, node->args, lash);
	else if (node->type == REDIR_IN || node->type == REDIR_OUT
		|| node->type == REDIR_APP)
		execute_redirs(node, lash);
}
