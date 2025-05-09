#include "../minishell.h"

int	check_access(char *path, t_mini *lash)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
			return (0);
		ft_putstr_fd("lash :", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		lash->exit_code = 126;
		return (1);
	}
	return (2);
}

void	*fail_to_malloc(t_mini *lash)
{
	ft_putstr_fd("Cannot allocate memory, please exit lash\n", 2);
	lash->exit_code = 1;
	return (NULL);
}

void	cmd_error(char *cmd, t_mini *lash)
{
	ft_putstr_fd("lash: ", 2);
	ft_putstr_fd(cmd, 2);
	if (ft_strchr(cmd, '/') != NULL)
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
	lash->exit_code = 127;
}

void	wait_child(pid_t pid, t_mini *lash)
{
	waitpid(pid, &lash->exit_code, 0);
	if (WIFEXITED(lash->exit_code))
		lash->exit_code = WEXITSTATUS(lash->exit_code);
}
