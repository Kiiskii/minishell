#include "minishell.h"

void	execute_command(ast node, struct minishell)
{
	if (node->value == "cd")
		builtin_cd();
	else if (node->value == "pwd")
		builtin_pwd();
	else if (node->value == "export")
		builtin_export();
	else if (node->value == "unset")
		builtin_unset();
	else if (node->value == "env")
		builtin_env();
	else if (node->value == "echo")
		builtin_echo();
	else if (node->value == "exit")
		builtin_exit();
	else
		execute_externals(something, ms);


void	begin_execution(ast node, struct minishell)
{
	if (!node || !minishell)
		error_and_exit;
	if (node->type == PIPE)
		execute_pipe(node, ms);
	else if (node->type == COMMAND)
		execute_command(node, ms);
	else if (any other node type)
		execute_that_node;
}
