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

typedef struct s_envi
{
	char			*value;
	char			*key;
	int				has_value;
	struct s_envi	*next;
}		t_envi;

typedef struct s_token
{
	char			*token;
	t_token_type	type;
	struct s_token	*next;
}		t_token;

void	start_readline();
void	tokenize_input(char *input, t_token **list);
int		is_specialchar(char c);
int		ft_isblank(int c);
int		handle_redirs(t_token **list, char *str);
void	add_token(t_token **list, char *content, t_token_type type);
int		handle_words(t_token **list, char *str);
void	env_to_list(t_envi **envi, char **env);
t_envi	*create_node(t_envi *new_node, char *env, int j, int has_value);
void	add_back(t_envi *tmp, t_envi *new);

//for testing
void	execute_command(char **args, t_envi *env);
void	begin_execution(char *str, t_envi *env);

//builtins
int		builtin_cd(char **array, t_envi *env);
int		builtin_echo(char **array);
int		builtin_env(char **array, t_envi *env);
int		builtin_exit(char **array);
int		builtin_export(char **array, t_envi *env);
int		builtin_pwd(char **array);
int		builtin_unset(char **array, t_envi *env);

#endif
