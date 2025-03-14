#include "../minishell.h"

int	is_specialchar(char c)
{
	if (c == '|')
		return (1);
	if (c == '<' || c == '>')
		return (1);
	return (0);
}
