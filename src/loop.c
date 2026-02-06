/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:14:16 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/06 12:21:36 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ft_loop(t_shell *mini)
{
    char    *line;

    (void)mini;
    while (1)
    {
        // las lineas de abajo las ha hecho alepinto y es la implementacion del modo comando de bash
        if (ft_strncmp(av[1], "-c", 0))
            line = av[2];
        else
            line = readline("minishel> ");
        if (!ft_strncmp(line, "exit", 5))
            break ;
        if (*line)
        {
            //data = ft_set_tokens(line);
            add_history(line);
        }
    }
}
