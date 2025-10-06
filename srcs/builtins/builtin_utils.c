/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillen <lguillen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:32:15 by lguillen          #+#    #+#             */
/*   Updated: 2025/05/19 10:32:17 by lguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	not_valid_msg(char *str)
{
	ft_putstr_fd("lash: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

char	*find_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	if (str[i] == '=' && str[i - 1] == '+')
		i--;
	key = ft_substr(str, 0, i);
	return (key);
}

int	check_existing(char *str, t_envi *env)
{
	t_envi	*trav;
	char	*key;
	int		count;

	count = 0;
	trav = env;
	while (str[count] && str[count] != '=')
		count++;
	if (str[count] == '=' && str[count - 1] == '+')
		count--;
	key = ft_substr(str, 0, count);
	if (key == NULL)
		return (12);
	while (trav != NULL)
	{
		if (ft_strcmp(trav->key, key) == 0)
		{
			free(key);
			return (1);
		}
		trav = trav->next;
	}
	free(key);
	return (0);
}

void	error_cmd_not_found(char *cmd, t_mini *lash)
{
	ft_putstr_fd("Command '", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("' not found\n", 2);
	lash->exit_code = 127;
}
