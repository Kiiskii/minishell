#include "../minishell.h"

int	check_min_max(const char *str, long long nb, int sign, char *arg)
{
	if (nb > LLONG_MAX / 10 || (nb == INT64_MAX / 10 && ((sign == 1 && (*str
						- '0') > (LLONG_MAX % 10)) || (sign == -1 && (*str
						- '0') > (LLONG_MIN % 10)))))
	{
		ft_putstr_fd("lash: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (1);
	}
	return (0);
}

long long	ft_atoll(const char *nptr, char *arg)
{
	int			sign;
	long long	convert;

	sign = 1;
	convert = 0;
	while ((*nptr <= 13 && *nptr >= 9) || *nptr == 32)
		nptr++;
	if (*nptr == 43 || *nptr == 45)
	{
		if (*nptr == 45)
			sign *= -1;
		nptr++;
	}
	while (*nptr >= 48 && *nptr <= 57)
	{
		if (check_min_max(nptr, convert, sign, arg))
			return (2);
		convert = convert * 10 + (*nptr - '0');
		nptr++;
	}
	convert *= sign;
	return (convert);
}

int	only_digits(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_ast *ast, char **array, t_mini *lash)
{
	ft_putstr_fd("exit\n", 2);
	if (!array[1])
		exit_process(ast, lash);
	else if (only_digits(array[1]))
	{
		if (array[2])
			ft_putstr_fd("lash: exit: too many arguments\n", 2);
		else
		{
			lash->exit_code = ft_atoll(array[1], array[1]);
			exit_process(ast, lash);
		}
	}
	else
	{
		ft_putstr_fd("lash: exit: ", 2);
		ft_putstr_fd(array[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		lash->exit_code = 2;
		exit_process(ast, lash);
	}
	return (1);
}
