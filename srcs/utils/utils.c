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

int	iterate_key(char *token)
{
	int	i;

	i = 0;
	while (ft_isalnum(token[i]) || token[i] == '_')
		i++;
	return (i);
}

int	iterate_quotes(char *str, char quote)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}
