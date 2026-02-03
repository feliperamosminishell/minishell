/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:37:01 by goramos-          #+#    #+#             */
/*   Updated: 2026/02/03 03:42:55 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

static int	echo_aux (char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (10);
	else
	{
		i++;
		while(arg)
		{
			if (arg[i] == 'n')
				i++;
			if (arg[i] != 'n' && arg[i] != '\0' && !(arg[i - 1] == '-'))
				return (10);
			if ((arg[i - 1] == 'n') && arg[i] == '\0')
				return (20);
		}
		return (0);
	}
}

int	builtin_echo(char **argv)
{
	int	i;
	int	flag_nl;
	int	check;
	int	j;

	flag_nl = 0;
	i = 1;//PREGUNTAR FELIPE POR TEMA PARSEO COMO ME LLEGA SI CMD + ARGS o solo ARGS
	while(argv[i])
	{
		j = echo_aux(argv[i]);
		if (j == 10)
			break;
		else if (j == 20)
		{
			flag_nl = 1;
		}
		i++;
	}
	while (argv[i])
	{
		printf("%s",argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (flag_nl == 0)
		printf("\n");
	return (0);
}
