/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillen <lguillen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:42:04 by lguillen          #+#    #+#             */
/*   Updated: 2025/05/19 10:42:05 by lguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*wrap_join(char *s1, char *s2)
{
	char	*string;

	if (!s1 || !s2)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	string = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (!string)
		return (NULL);
	return (string);
}

void	delete_heredoc_temps(t_ast *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		delete_heredoc_temps(tree->left);
	if (tree->right)
		delete_heredoc_temps(tree->right);
	if (tree->filename && tree->fd != -1)
		unlink(tree->filename);
}

void	sig_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}

void	add_back(t_envi *tmp, t_envi *node)
{
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
	else
		tmp = node;
}
