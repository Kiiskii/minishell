#include "../minishell.h"

void	execute_command(char **args, t_envi *env)
{
	int	exit_code;

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
		builtin_exit(args);
//	else
//		execute_externals(something, ms);
}

void	begin_execution(char *str, t_envi *env)
{
	char	**arr;

	arr = ft_split(str, ' ');
	execute_command(arr, env);
}
//
//void	begin_execution(ast node, struct minishell)
//{
//	if (!node || !minishell)
//		error_and_exit;
//	if (node->type == PIPE)
//		execute_pipe(node, ms);
//	else if (node->type == COMMAND)
//		execute_command(node, ms);
//	else if (any other node type)
//		execute_that_node;
//}
