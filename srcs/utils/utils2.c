#include "../minishell.h"

char	*wrap_join(char *s1, char *s2)
{
	char	*string;

	if (!s1 || !s2)
		return (NULL);
	string = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (!string)
		return (NULL);
	return (string);
}
