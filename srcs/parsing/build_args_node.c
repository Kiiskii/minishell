#include "../minishell.h"

char	**fill_array(t_token *list, char **args)
{
	int	i;

	i = 0;
	if (list->type == PIPE)
		list = list->next;
	if (!args)
		return (NULL);
	while (list && list->type != PIPE)
	{
		if (list->type >= REDIR_IN && list->type <= REDIR_APP)
			list = list->next->next;
		else
		{
			args[i] = ft_strdup(list->token);
			if (!args[i])
			{
				free_arr(args);
				return (NULL);
			}
			list = list->next;
			i++;
		}
	}
	args[i] = NULL;
	return (args);
}
/*
char	**alloc_args(t_token *list, char **args)
{
	int	len;
	int	i;

	i = 0;
	if (list->type == PIPE)
		list = list->next;
	while (list && list->type != PIPE)
	{
		len = 0;
		if (list->type >= REDIR_IN && list->type <= REDIR_APP)
			list = list->next->next;
		else
		{
			len = ft_strlen(list->token);
			args[i] = malloc(len + 1);
			if (!args[i])
				return (NULL);
			list = list->next;
			i++;
		}
	}
	args[i] = NULL;
	return (args);
}
*/

int	count_tokens(t_token *list)
{
	int		token_count;

	token_count = 0;
	if (list->type == PIPE)
		list = list->next;
	while (list && list->type != PIPE)
	{
		//Make sure this no break
		if (list->type >= REDIR_IN && list->type <= REDIR_APP)
			list = list->next->next;
		else
		{
			token_count++;
			list = list->next;
		}
	}
	return (token_count);
}

char	**list_to_array(t_token *list)
{
	t_token	*tmp;
	char	**args;
	int		token_count;

	tmp = list;
	token_count = 0;
	token_count = count_tokens(tmp);
	args = malloc((token_count + 1) * (sizeof(char *)));
	if (!args)
		return (NULL);
	//args = alloc_args(tmp, args);
	args = fill_array(tmp, args);
	return (args);
}
