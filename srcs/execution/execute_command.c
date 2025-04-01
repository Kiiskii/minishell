#include "../minishell.h"

void    execute_command(char **args, t_envi *env) //takes ast root, lash struct (which contains exitcode?)
{
	if (ft_strncmp(args[0], "cd", 2) == 0)
		exit_code = builtin_cd(args, env);
	else if (ft_strncmp(args[0], "pwd", 3) == 0)
		exit_code = builtin_pwd(args);
	else if (ft_strncmp(args[0], "export", 8) == 0)
		exit_code = builtin_export(args, env);
	else if (ft_strncmp(args[0], "unset", 8) == 0)
		exit_code = builtin_unset(args, env);
	else if (ft_strncmp(args[0], "env", 8) == 0)
		exit_code = builtin_env(args, env);
	else if (ft_strncmp(args[0], "echo", 8) == 0)
		exit_code = builtin_echo(args);
	else if (ft_strncmp(args[0], "exit", 8) == 0)
		exit_code = builtin_exit(args);
	else
		execute_externals(root, env, lash);
}
