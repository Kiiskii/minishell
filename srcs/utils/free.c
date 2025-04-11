#include "../minishell.h"

void	free_tokens(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	while (list)
	{
		list = list->next;
		free(tmp->token);
		free(tmp);
		tmp = list;
	}
}
