/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:37:01 by goramos-          #+#    #+#             */
/*   Updated: 2026/02/03 00:39:59 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

int	builtin_echo(char **argv)
{
	int	i;
	int	flag_nl;

	flag_nl = 1;
	i = 1;
	if (argv[1] && argv[1][0] == '-' && argv[1][1] == 'n' && argv[1][2] == '\0')
	{
		flag_nl = 0;
		i = 2;
	}
	while (argv[i])
	{
		printf("%s",argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (flag_nl == 1)
		printf("\n");
	return (0);
}
