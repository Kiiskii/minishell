#include "../minishell.h"

void	reset_default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handle_sig_int_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		close(STDIN_FILENO);
		rl_done = 1;
		g_signum = SIGINT;
	}
}

void	init_signals_heredoc(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = &handle_sig_int_heredoc;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sig_int(int signum)
{
	if (signum == SIGINT)
	{
		g_signum = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_signals(void)
{
	struct sigaction	sa_int;

	g_signum = 0;
	sa_int.sa_handler = &handle_sig_int;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, SIG_IGN);
	//if (WIFEXITED(lash->exit_code))
	//	lash->exit_code = WEXITSTATUS(lash->exit_code);
}
