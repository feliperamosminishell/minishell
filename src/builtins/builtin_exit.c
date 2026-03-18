/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:09:31 by goramos-          #+#    #+#             */
/*   Updated: 2026/03/18 00:10:03 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_isnum(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static long long	ft_atoi_long(const char *str, int *overflow)
{
	long long	result;
	long long	sign;
	int			i;

	result = 0;
	sign = 1;
	*overflow = 0;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > (LLONG_MAX - (str[i] - '0')) / 10)
		{
			*overflow = 1;
			return (0);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static void	exit_numeric_error(t_shell *shell, char **argv)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(argv[1], STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	ft_free_cmds(&shell->cmds);
	free_env(shell->env);
	exit(2);
}

static void	exit_too_many(t_shell *shell)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	shell->exit_status = 1;
}

void	builtin_exit(t_shell *shell, char **argv)
{
	long long	val;
	int			overflow;
	int			argc;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	argc = 0;
	while (argv[argc])
		argc++;
	if (argc == 1)
	{
		ft_free_cmds(&shell->cmds);
		free_env(shell->env);
		exit(shell->exit_status);
	}
	if (!ft_isnum(argv[1]))
		exit_numeric_error(shell, argv);
	if (argc > 2)
		return (exit_too_many(shell));
	val = ft_atoi_long(argv[1], &overflow);
	if (overflow)
		exit_numeric_error(shell, argv);
	ft_free_cmds(&shell->cmds);
	free_env(shell->env);
	exit((unsigned char)val);
}