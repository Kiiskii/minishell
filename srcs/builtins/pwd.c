/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillen <lguillen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:33:04 by lguillen          #+#    #+#             */
/*   Updated: 2025/05/19 10:33:06 by lguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pwd(t_envi *env, char **pwd_path)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->key, "PWD") == 0)
		{
			if (env->value)
			{
				*pwd_path = ft_strdup(env->value);
				if (!(*pwd_path))
				{
					ft_putstr_fd("Cannot allocate memory,", 2);
					ft_putstr_fd(" please CTRL + D!\n", 2);
					return (12);
				}
				return (0);
			}
		}
		env = env->next;
	}
	return (1);
}

int	print_from_env(char *pwd_path)
{
	if (pwd_path)
	{
		if (pwd_path)
			printf("%s\n", pwd_path);
		free(pwd_path);
		return (0);
	}
	return (1);
}

int	builtin_pwd(char **array, t_envi *env)
{
	char	*pathname;
	char	*pwd_path;

	pwd_path = NULL;
	if (array[1] && array[1][0] == '-')
	{
		printf("lash: pwd: options for pwd are not supported\n");
		return (2);
	}
	if (check_pwd(env, &pwd_path) != 0)
		return (1);
	pathname = getcwd(NULL, 0);
	if (!pathname)
	{
		if (print_from_env(pwd_path) == 0)
			return (0);
		perror("lash: pwd: getcwd");
	}
	if (pathname)
		printf("%s\n", pathname);
	free(pathname);
	free(pwd_path);
	return (0);
}
