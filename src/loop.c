/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:14:16 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/07 17:23:41 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ft_loop(t_shell *mini)
{
    char    *line;

    (void)mini;
    while (1)
    {
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