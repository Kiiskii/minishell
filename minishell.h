#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <limits.h>
# include <signal.h>

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

typedef struct s_indexer
{
	int		i;
	int		j;
	char	*str;
}		t_indexer;

typedef struct s_mini
{
	t_envi	*env;
	int		fd_in;
	int		fd_out;
	int		exit_code;
}		t_mini;

void	start_readline(t_mini *lash);
void	env_to_list(t_envi **envi, char **env);

// signals
void	reset_default_signals(void);
void	handle_sig_int(int signum);
void	init_signals(void);

// parsing errors
int		error_iterate_list(t_token *tokens, t_mini *lash);
void	error_redir(t_token *tokens, t_mini *lash);
int		error_token(t_token *tokens, t_mini *lash);
int		error_input(char *input, t_mini *lash);
int		error_quotes(char *input);
int		error_pipe_end(char *input);

// tokenizing
void	tokenize_input(char *input, t_token **list);
int		is_specialchar(char c);
int		ft_isblank(int c);
int		handle_redirs(t_token **list, char *str);
void	add_token(t_token **list, char *content, t_token_type type);
int		handle_words(t_token **list, char *str);
void	iterate_word(t_indexer *s);
int		begin_tokenizing(t_token **tokens, t_mini *lash, char *input);

// re-tokenize
void	re_tokenize(t_token **tokens);
void	parse_token(t_token *current, int i, int j, int *malloc_fail);
int		iterate_quotes(char *str, char quote);
void	add_next_token(t_token **new_tokens, char *word, int *malloc_fail);
void	replace_tokens(t_token **current, t_token *new_tokens);

// expansions & quotes
char	*iterate_token_help(t_indexer *s, t_mini *lash, char *new_token, int *in_dquotes);
char	*handle_quotes(char *new_token, t_indexer *s, char quote);
char	*handle_exps(t_indexer *s, t_mini *lash, char *new_token);
int		iterate_key(char *token);
char	*iterate_token_exp(t_indexer *s, t_mini *lash);
void	expand_tokens(t_token **tokens, t_mini *lash);
char	*find_env_match(char *my_key, t_envi *env);
char	*exps_find_key(char *token, t_envi *env);
char	*iterate_token(t_indexer *s);
int		iterate_quotes(char *str, char quote);
void	remove_quotes(t_token **tokens, t_mini *lash);

// building ast
t_envi	*create_node(t_envi *new_node, char *env, int j, int has_value);
void	add_back(t_envi *tmp, t_envi *new); //why is new a different colour?

//for testing
void	execute_command(t_ast *ast, char **args, t_mini *lash);
void	begin_execution(t_ast *ast, t_mini *lash);
void	exit_process(t_ast *ast, t_mini *lash);

t_ast	*build_ast(t_token **list);
t_ast	*create_tree(t_ast *tree, t_token *list, t_token_type type);
t_ast	*build_right(t_token *list);
t_ast	*create_redir(t_token_type redir, char *filename, t_ast *branch);
t_ast	*create_args(char **args, t_ast *branch);
char	**list_to_array(t_token *list);
char	**alloc_args(t_token *list, char **args);
char	**fill_array(t_token *list, char **args);
t_ast	*add_node_right(t_ast *node, t_ast *new_node);
t_ast	*add_node_left(t_ast *node, t_ast *new_node);

// free functions
void	malloc_fail_message(t_token **tokens);
void	free_tokens(t_token **list);
void	free_ast(t_ast *tree);
void	free_args(char **args);
void	free_branch(t_ast *branch);
void	free_env(t_envi *env);

//builtins
int		builtin_cd(char **array, t_envi *env);
int		builtin_echo(char **array);
int		builtin_env(char **array, t_envi *env);
int		builtin_exit(t_ast *ast, char **array, t_mini *lash);
void	builtin_export(char **array, t_envi *env, t_mini *lash);
int		builtin_pwd(char **array);
int		builtin_unset(char **array, t_envi *env);

//env functions
int	add_to_env(char *str, t_envi *env);
char	*find_key(char *str);
int	print_alphabetised(t_envi *env);
int	add_new(char *str, t_envi *env);

//builtin utils
void	free_list(t_envi **head);
void	not_valid_msg(char *str);
char	*find_key(char *str);
int	check_existing(char *str, t_envi *env);
void	error_cmd_not_found(char *cmd, t_mini *lash);

//pipes
void	execute_pipe(t_ast *root, t_mini *lash);
void	go_left(t_ast *node, t_mini *lash, int *fds, int *pid);
void	go_right(t_ast *node, t_mini *lash, int *fds, int *pid);
//void	prepare_pipe(int *fds, t_mini *lash);

//externals
void	handle_exit_status(char *path, t_mini *lash);
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
//void	execute_heredoc(t_ast *node, t_mini *lash);

#endif
