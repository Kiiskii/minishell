/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillen <lguillen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:32:04 by lguillen          #+#    #+#             */
/*   Updated: 2025/05/19 11:06:54 by lguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

sig_atomic_t	g_signum = 0;

int	begin_tokenizing(t_token **tokens, t_mini *lash, char *input)
{
	tokenize_input(input, tokens);
	if (!tokens)
		return (0);
	if (error_iterate_list(*tokens, lash) == 0)
	{
		free_tokens(tokens);
		return (0);
	}
	expand_tokens(tokens, lash);
	remove_quotes(tokens);
	if (!tokens || !*tokens)
		return (0);
	if (error_iterate_list(*tokens, lash) == 0)
	{
		free_tokens(tokens);
		return (0);
	}
	return (1);
}

int	build_shell(t_token **tokens, t_mini *lash)
{
	t_ast	*tree;
	int		error;

	error = 0;
	tree = build_ast(tokens, &error);
	free_tokens(tokens);
	if (!tree)
	{
		malloc_fail_message_tree(tree);
		return (0);
	}
	error = iterate_heredoc(tree, lash, 0);
	if (error == -2)
	{
		delete_heredoc_temps(tree);
		malloc_fail_message_tree(tree);
		return (0);
	}
	lash->head = tree;
	if (lash->heredoc_sig != 1 && error == 0)
		begin_execution(tree, lash);
	delete_heredoc_temps(tree);
	free_ast(tree);
	lash->heredoc_sig = 0;
	return (1);
}

void	start_readline(t_mini *lash)
{
	char	*input;
	t_token	*tokens;

	while (1)
	{
		init_signals();
		dup2(lash->fd_in, STDIN_FILENO);
		tokens = NULL;
		input = readline("lash$: ");
		if (!input)
			break ;
		if (input[0] == '\0' || error_input(input, lash) == 0)
		{
			free(input);
			continue ;
		}
		add_history(input);
		if (begin_tokenizing(&tokens, lash, input) == 0)
			continue ;
		if (build_shell(&tokens, lash) == 0)
			continue ;
		free(input);
		g_signum = 0;
	}
}

void	init_lash(t_mini *lash)
{
	lash->exit_code = 0;
	lash->fd_in = -1;
	lash->heredoc_sig = 0;
	lash->fd_in = dup(STDIN_FILENO);
	if (lash->fd_in == -1)
		exit(1);
}

int	main(int argc, char **argv, char **env)
{
	t_envi	*envi;
	t_mini	lash;

	if (argc != 1)
		return (1);
	(void)argv;
	envi = NULL;
	env_to_list(&envi, env);
	if (!envi)
	{
		ft_putstr_fd("Cannot allocate memory for env!\n", 2);
		return (1);
	}
	ft_memset(&lash, 0, sizeof(t_mini));
	lash.env = envi;
	init_lash(&lash);
	start_readline(&lash);
	close(lash.fd_in);
	free_env(lash.env);
	printf("Exiting lash...\n");
	return (lash.exit_code);
}
