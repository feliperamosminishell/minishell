/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:26:31 by goramos-          #+#    #+#             */
/*   Updated: 2026/02/03 22:40:43 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

int	builtin_pwd(t_shell *sh)
{
	char	*cwd;

	if (!sh || !sh->pwd)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			perror("pwd");
			return (1);
		}
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		free(cwd);
		return (0);
	}
	write(1, sh->pwd, ft_strlen(sh->pwd));
	write(1, "\n", 1);
	return (0);
}
