#include "../minishell.h"

//char	**env_to_arr(t_envi *env) I think this is in externals.c
//{
//	char	*tmp;
//	char	**res;
//	int		i;
//
//	i = 0;
//	if (!(tmp = malloc(env_size(env)) + 1 * sizeof(char)))
//		return (NULL);
//	while (env && env->next != NULL)
//	{
//		if (env->has_value == 1)
//			node_to_str(env, tmp, &i);
//		if (env->next->next != NULL)
//			tmp[i++] = '\n';
//		env = env->next;
//	}
//	tmp[i] = '\0';
//	res = ft_split(tmp, '\n'); //check if exists?
//	free(tmp); //check if exists?
//	return (res);
//}

//void	execute_tree(t_ast *ast, t_mini *lash)
//{
	
void	begin_execution(t_ast *ast, t_mini *lash)
{
//	char	**arr;

//	arr = ft_split(str, ' ');
//	execute_command(arr, lash);
//	free(arr);
	//Here would actually be info taken from ast root
	if (!ast || !lash)
		return ;
	if (ast->type == PIPE)
		execute_pipe(ast, lash);
	else if (ast->type == WORD)
		execute_command(ast->args, lash);
	else if (ast->type == REDIR_IN || ast->type == REDIR_OUT || ast->type == REDIR_APP) //HEREDOC can you say >= REDIR_IN && <= REDIR_APP
		execute_redirs(ast, lash);
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
