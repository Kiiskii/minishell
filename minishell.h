#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	REDIR_OUT_APPEND
}		t_token_type;

typedef struct s_token
{
	char			*token;
	struct s_token	*next;
	t_token_type	type;
}		t_token;

#endif
