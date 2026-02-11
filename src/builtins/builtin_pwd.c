/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:26:31 by goramos-          #+#    #+#             */
/*   Updated: 2026/02/11 14:08:27 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int	builtin_pwd(t_shell *sh)
{
	if (!sh->pwd_data.pwd)
		return (1);
	write(1, sh->pwd_data.pwd, ft_strlen(sh->pwd_data.pwd));
	write(1, "\n", 1);
	return (0);
}
