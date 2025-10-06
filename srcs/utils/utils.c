/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillen <lguillen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:42:12 by lguillen          #+#    #+#             */
/*   Updated: 2025/05/19 10:42:13 by lguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_specialchar(char c)
{
	if (c == '|')
		return (1);
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_isblank(int c)
{
	if (c == '\t' || c == '\n' || c == ' ')
		return (1);
	return (0);
}

int	iterate_key(char *token)
{
	int	i;

	i = 0;
	while (ft_isalnum(token[i]) || token[i] == '_')
		i++;
	return (i);
}

int	iterate_quotes(char *str, char quote)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}

void	handle_exit_status(t_mini *lash)
{
	if (WIFEXITED(lash->exit_code))
		lash->exit_code = WEXITSTATUS(lash->exit_code);
	else if (WIFSIGNALED(lash->exit_code))
	{
		write(STDOUT_FILENO, "\n", 1);
		lash->exit_code = 128 + WTERMSIG(lash->exit_code);
	}
}
