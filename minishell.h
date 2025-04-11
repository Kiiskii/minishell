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
void	add_back(t_envi *tmp, t_envi *new);
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
