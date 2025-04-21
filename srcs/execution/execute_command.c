#include "../minishell.h"

void    execute_command(char **args, t_mini *lash)
{
	if (ft_strcmp(args[0], "cd") == 0)
		lash->exit_code = builtin_cd(args, lash->env);
	else if (ft_strcmp(args[0], "pwd") == 0)
		lash->exit_code = builtin_pwd(args, lash->env);
	else if (ft_strcmp(args[0], "export") == 0)
		lash->exit_code = builtin_export(args, lash->env);
	else if (ft_strcmp(args[0], "unset") == 0)
		lash->exit_code = builtin_unset(args, lash->env);
	else if (ft_strcmp(args[0], "env") == 0)
		lash->exit_code = builtin_env(args, lash->env);
	else if (ft_strcmp(args[0], "echo") == 0)
		lash->exit_code = builtin_echo(args);
	else if (ft_strcmp(args[0], "exit") == 0)
		lash->exit_code = builtin_exit(args, lash);
	else
		execute_external(args, lash);
}
