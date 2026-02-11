/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:26:31 by goramos-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/02/08 06:28:54 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
=======
/*   Updated: 2026/02/04 16:22:32 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"
>>>>>>> main

int	builtin_pwd(t_shell *sh)
{
	if (!sh->pwd_data.pwd)
		return (1);
	write(1, sh->pwd_data.pwd, ft_strlen(sh->pwd_data.pwd));
	write(1, "\n", 1);
	return (0);
}
