/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:48:32 by juan-her          #+#    #+#             */
/*   Updated: 2026/01/31 16:33:52 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_init_shell(t_shell *mini, char **ev)
{
    mini->env = ev;
    mini->exit_status = 0;
}
int main(int ac, char **ag, char **env)
{
    t_shell mini;
    
    (void) ac;
    (void) ag;
    ft_init_shell(&mini, env);
    ft_loop(&mini);
}