/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillen <lguillen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:39:36 by lguillen          #+#    #+#             */
/*   Updated: 2025/05/19 10:39:37 by lguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_protected(t_envi *new_node, t_envi *second_node)
{
	new_node->next = second_node;
	second_node->has_value = 1;
	second_node->key = ft_strdup("_");
	second_node->value = ft_strdup("/usr/bin/env");
	if (!second_node->key || !second_node->value)
	{
		free(new_node);
		free(new_node->key);
		free(new_node->value);
		free(second_node);
		free(second_node->key);
		free(second_node->value);
		second_node = NULL;
		return ;
	}
	second_node->next = NULL;
}

t_envi	*create_shlvl(void)
{
	t_envi	*new_node;
	t_envi	*second_node;

	new_node = ft_calloc(1, sizeof(t_envi));
	if (!new_node)
		return (NULL);
	new_node->has_value = 1;
	new_node->key = ft_strdup("SHLVL");
	new_node->value = ft_strdup("1");
	second_node = ft_calloc(1, sizeof(t_envi));
	if (!new_node->key || !new_node->value || !second_node)
	{
		free(new_node);
		free(new_node->key);
		free(new_node->value);
		return (NULL);
	}
	create_protected(new_node, second_node);
	if (!second_node)
		return (NULL);
	return (new_node);
}

t_envi	*create_node(t_envi *new_node, char *env, int j, int has_value)
{
	new_node->has_value = has_value;
	new_node->key = ft_substr(env, 0, j);
	if (!new_node->key)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	if (has_value)
	{
		new_node->value = ft_strdup(&env[j + 1]);
		if (!new_node->value)
		{
			free(new_node->key);
			free(new_node);
			return (NULL);
		}
	}
	else
		new_node->value = NULL;
	return (new_node);
}

t_envi	*check_for_value(t_envi *new_node, char *str, int j, t_envi *envi)
{
	if (str[j] == '=')
	{
		new_node = create_node(new_node, str, j, 1);
		if (!new_node)
		{
			free_env(envi);
			return (NULL);
		}
	}
	else
	{
		new_node = create_node(new_node, str, j, 0);
		if (!new_node)
		{
			free_env(envi);
			return (NULL);
		}
	}
	return (new_node);
}

void	env_to_list(t_envi **envi, char **env)
{
	int		i;
	int		j;
	t_envi	*new_node;

	i = 0;
	while (env[i])
	{
		j = 0;
		new_node = ft_calloc(1, sizeof(t_envi));
		if (!new_node)
			return ;
		while (env[i][j] && env[i][j] != '=')
			j++;
		new_node = check_for_value(new_node, env[i], j, *envi);
		if (!new_node)
			return ;
		if (!*envi)
			*envi = new_node;
		else
			add_back(*envi, new_node);
		i++;
	}
	if (!*envi)
		*envi = create_shlvl();
}
