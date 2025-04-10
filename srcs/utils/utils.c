#include "../minishell.h"

int	is_specialchar(char c)
{
	if (c == '|')
		return (1);
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_isblank(int c)
{
	if (c == '\t' || c == '\n' || c == ' ')
		return (1);
	return (0);
}
