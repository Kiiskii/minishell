/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillen <lguillen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:35:58 by lguillen          #+#    #+#             */
/*   Updated: 2025/05/19 10:35:59 by lguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_command(t_ast *ast, char **args, t_mini *lash)
{
	if (ft_strcmp(args[0], "cd") == 0)
		lash->exit_code = builtin_cd(args, lash->env);
	else if (ft_strcmp(args[0], "pwd") == 0)
		lash->exit_code = builtin_pwd(args, lash->env);
	else if (ft_strcmp(args[0], "export") == 0)
		builtin_export(args, lash->env, lash);
	else if (ft_strcmp(args[0], "unset") == 0)
		lash->exit_code = builtin_unset(args, &lash->env);
	else if (ft_strcmp(args[0], "env") == 0)
		lash->exit_code = builtin_env(args, lash->env);
	else if (ft_strcmp(args[0], "echo") == 0)
		lash->exit_code = builtin_echo(args);
	else if (ft_strcmp(args[0], "exit") == 0)
		lash->exit_code = builtin_exit(args, lash);
	else
		execute_external(ast, lash);
}
