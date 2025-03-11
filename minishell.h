#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>

typedef enum e_toke_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
}		t_token_type;

typedef struct s_token
{
	char			**tokens;
	t_token_type	type;
}		t_token;

typedef struct s_command
{
	char	*command;
	int		token_count;
}		t_command;

#endif
