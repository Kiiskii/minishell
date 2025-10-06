/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillen <lguillen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:32:39 by lguillen          #+#    #+#             */
/*   Updated: 2025/05/19 10:32:41 by lguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(char **array, t_envi *env)
{
	t_envi	*trav;

	if (array[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd("options and arguments for env are not supported\n", 2);
		return (125);
	}
	trav = env;
	while (trav != NULL)
	{
		if (trav->value != NULL)
		{
			printf("%s", trav->key);
			printf("=");
			printf("%s\n", trav->value);
		}
		trav = trav->next;
	}
	return (0);
}
