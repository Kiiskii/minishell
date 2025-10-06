/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillen <lguillen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:39:46 by lguillen          #+#    #+#             */
/*   Updated: 2025/05/19 10:39:47 by lguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_quotes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"')
		{
			i++;
			while (input[i] && input[i] != '"')
				i++;
			if (input[i] == '\0')
				return (0);
		}
		if (input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '\'')
				i++;
			if (input[i] == '\0')
				return (0);
		}
		i++;
	}
	return (1);
}

int	error_pipe_end(char *input)
{
	int	last;
	int	i;

	i = 0;
	while (isblank(input[i]))
		i++;
	if (input[i] == '|')
		return (0);
	last = ft_strlen(input) - 1;
	if (input[last] == '|')
		return (0);
	return (1);
}

int	error_input(char *input, t_mini *lash)
{
	int	error;

	if (ft_strlen(input) > INPUT_MAX_LEN)
	{
		ft_putstr_fd("lash: syntax error: input too long!\n", 2);
		lash->exit_code = 2;
		return (0);
	}
	error = error_quotes(input);
	if (error == 0)
	{
		ft_putstr_fd("lash: syntax error: unclosed quotes\n", 2);
		lash->exit_code = 2;
		return (0);
	}
	error = error_pipe_end(input);
	if (error == 0)
	{
		ft_putstr_fd("lash: syntax error near token `|'\n", 2);
		lash->exit_code = 2;
		return (0);
	}
	return (1);
}
