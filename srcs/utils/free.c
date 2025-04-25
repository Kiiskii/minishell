#include "../minishell.h"

void	free_tokens(t_token **list)
{
	t_token	*tmp;

	tmp = *list;
	while (*list)
	{
		*list = (*list)->next;
		if (tmp)
		{
			if (tmp->token || tmp->token[0] != '\0')
				free(tmp->token);
			free(tmp);
		}
		tmp = *list;
	}
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_ast(t_ast *tree)
{
	if (!tree)
		return ;
	free_ast(tree->left);
	free_ast(tree->right);
	if (tree->filename)
		free(tree->filename);
	if (tree->args)
		free_args(tree->args);
	free(tree);
}

void	free_env(t_envi *env)
{
	t_envi	*tmp;

	tmp = env;
	while (env)
	{
		env = env->next;
		free(tmp->value);
		free(tmp->key);
		free(tmp);
		tmp = env;
	}
}
