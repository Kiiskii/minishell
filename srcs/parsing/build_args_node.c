/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_args_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillen <lguillen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:38:33 by lguillen          #+#    #+#             */
/*   Updated: 2025/05/19 10:38:34 by lguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**fill_array(t_token *list, char **args)
{
	int	i;

	i = 0;
	if (list->type == PIPE)
		list = list->next;
	if (!args)
		return (NULL);
	while (list && list->type != PIPE)
	{
		if (list->type >= REDIR_IN && list->type <= REDIR_APP)
			list = list->next->next;
		else
		{
			args[i] = ft_strdup(list->token);
			if (!args[i])
			{
				free_arr(args);
				return (NULL);
			}
			list = list->next;
			i++;
		}
	}
	args[i] = NULL;
	return (args);
}

int	count_tokens(t_token *list)
{
	int		token_count;

	token_count = 0;
	if (list->type == PIPE)
		list = list->next;
	while (list && list->type != PIPE)
	{
		if (list->type >= REDIR_IN && list->type <= REDIR_APP)
			list = list->next->next;
		else
		{
			token_count++;
			list = list->next;
		}
	}
	return (token_count);
}

char	**list_to_array(t_token *list)
{
	t_token	*tmp;
	char	**args;
	char	**tmp_args;
	int		token_count;

	tmp = list;
	token_count = 0;
	token_count = count_tokens(tmp);
	args = ft_calloc((token_count + 1), (sizeof(char *)));
	if (!args)
		return (NULL);
	tmp_args = args;
	args = fill_array(tmp, args);
	if (!args)
		free(tmp_args);
	return (args);
}

t_ast	*handle_arguments(t_token *list, t_ast *branch)
{
	char	**cmd_args;

	cmd_args = list_to_array(list);
	if (!cmd_args)
		return (NULL);
	if (cmd_args[0] != NULL)
		branch = create_args(cmd_args, branch);
	else
		free(cmd_args);
	return (branch);
}
