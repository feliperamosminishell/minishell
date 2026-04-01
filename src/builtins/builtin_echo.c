/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:37:01 by goramos-          #+#    #+#             */
/*   Updated: 2026/04/01 01:55:01 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_n_flag(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	i++;
	if (arg[i] != 'n')
		return (0);
	while (arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (1);
	return (0);
}

int	builtin_echo(char **argv)
{
	int	i;
	int	flag_nl;

	flag_nl = 1;
	i = 1;
	while (argv[i] && is_valid_n_flag(argv[i]))
	{
		flag_nl = 0;
		i++;
	}
	while (argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (flag_nl)
		write(1, "\n", 1);
	return (0);
}
