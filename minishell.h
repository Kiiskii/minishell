#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>
#include <limits.h>

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
	struct s_token	*next;
	t_token_type	type;
}		t_token;

typedef struct s_mini
{
	t_envi	*env;
	int		fd_in;
	int		fd_out;
	int		exit_code;
}		t_mini;

void	start_readline();
void	tokenize_input(char *input, t_token **list);
int		is_specialchar(char c);
int		handle_redirs(t_token **list, char *str);
void	add_token(t_token **list, char *content, t_token_type type);
int		handle_words(t_token **list, char *str);
void	env_to_list(t_envi **envi, char **env);
t_envi	*create_node(t_envi *new_node, char *env, int j, int has_value);
void	add_back(t_envi *tmp, t_envi *new); //why is new a different colour?

//for testing
void	execute_command(char **args, t_mini *lash);
void	begin_execution(char *str, t_mini *lash);
void	exit_process(t_mini *lash); //(t_ast *ast, t_mini *lash);

//builtins
int		builtin_cd(char **array, t_envi *env);
int		builtin_echo(char **array);
int		builtin_env(char **array, t_envi *env);
int		builtin_exit(char **array, t_mini *lash);
int		builtin_export(char **array, t_envi *env);
int		builtin_pwd(char **array, t_envi *env);
int		builtin_unset(char **array, t_envi *env);

//env functions
void	add_to_env(char *str, t_envi *env);
char	*find_key(char *str);
int	print_alphabetised(t_envi *env);
void	add_new(char *str, t_envi *env);

//builtin utils
void	free_list(t_envi **head);

//pipes
//void	execute_pipe(t_ast *root, t_mini *lash);
//void	go_left(t_ast *node, t_mini *lash, int *fds, int *pid);
//void	go_right(t_ast *node, t_mini *lash, int *fds, int *pid);
//void	prepare_pipe(int *fds, t_mini *lash);

//externals
void	execute_external(char **args, t_mini *lash);
char	**get_bin(char **args, t_mini *lash, t_envi *env);
char	*find_path(char **paths, char *path, char *cmd);
char	**env_to_arr(t_envi *env);
int		env_size(t_envi *env);
void	node_to_str(t_envi *env, char *tmp, int *i);

//redirections
//int		execute_redirs(head, lash);
//void	redirect_in(t_ast *head, t_shell *lash);
//void	redirect_out(t_ast *head, t_shell *lash);
//void	redirect_outapp(t_ast *head, t_shell *lash);

#endif
