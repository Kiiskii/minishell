#include "../minishell.h"

void	free_list(t_envi **head)
{
	t_envi	*tmp;

	tmp = *head;
	while (*head)
	{
		*head = (*head)->next;
		free(tmp);
		tmp = *head;
	}
}
