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
	REDIR_APP
}		t_token_type;

typedef struct s_ast
{
	struct s_ast	*left;
	struct s_ast	*right;
	t_token_type	type;
	char			*filename;
	char			**args;
}		t_ast;

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

typedef struct s_mini
{
	t_envi	*env;
	int		fd_in;
	int		fd_out;
	int		exit_code;
}		t_mini;

void	start_readline();
void	env_to_list(t_envi **envi, char **env);

// tokenizing
void	tokenize_input(char *input, t_token **list);
int		is_specialchar(char c);
int		ft_isblank(int c);
int		handle_redirs(t_token **list, char *str);
void	add_token(t_token **list, char *content, t_token_type type);
int		handle_words(t_token **list, char *str);
char	*concat_word(char *word, char *str, int len);
int		word_in_quotes(char **word, char *str, int i, int *j);

// building ast
t_envi	*create_node(t_envi *new_node, char *env, int j, int has_value);
void	add_back(t_envi *tmp, t_envi *new); //why is new a different colour?

//for testing
void	execute_command(char **args, t_mini *lash);
void	begin_execution(t_ast *ast, t_mini *lash);
void	exit_process(t_mini *lash); //(t_ast *ast, t_mini *lash);
t_ast	*build_ast(t_token *list);
t_ast	*create_tree(t_ast *tree, t_token *list, t_token_type type);
t_ast	*build_right(t_token *list);
t_ast	*create_redir(t_token_type redir, char *filename, t_ast *branch);
t_ast	*create_args(char **args, t_ast *branch);
char	**list_to_array(t_token *list);
char	**alloc_args(t_token *list, char **args);
char	**fill_array(t_token *list, char **args);

// free functions
void	free_tokens(t_token *list);

//builtins
int		builtin_cd(char **array, t_envi *env);
int		builtin_echo(char **array);
int		builtin_env(char **array, t_envi *env);
int		builtin_exit(char **array, t_mini *lash);
void		builtin_export(char **array, t_envi *env, t_mini *lash);
int		builtin_pwd(char **array, t_envi *env);
int		builtin_unset(char **array, t_envi *env);

//env functions
int	add_to_env(char *str, t_envi *env);
char	*find_key(char *str);
int	print_alphabetised(t_envi *env);
int	add_new(char *str, t_envi *env);

//builtin utils
void	free_list(t_envi **head);

//pipes
void	execute_pipe(t_ast *root, t_mini *lash);
int		go_left(t_ast *node, t_mini *lash, int *fds);
void	go_right(t_ast *node, t_mini *lash, int *fds, int *pid);
//void	prepare_pipe(int *fds, t_mini *lash);

//externals
void	execute_external(char **args, t_mini *lash);
char	**get_env_path(char **args, t_mini *lash, t_envi *env);
//char	**get_bin(char **args, t_mini *lash, t_envi *env);
//char	*find_path(char **paths, char *path, char *cmd);
char	**env_to_arr(t_envi *env);
//int		env_size(t_envi *env);
//void	node_to_str(t_envi *env, char *tmp, int *i);

//redirections
void		execute_redirs(t_ast *head, t_mini *lash);
void	redirect_in(t_ast *head, t_mini *lash);
void	redirect_out(t_ast *head, t_mini *lash);
void	redirect_outapp(t_ast *head, t_mini *lash);
void	execute_heredoc(t_ast *node, t_mini *lash);

#endif
