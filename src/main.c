/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:48:32 by juan-her          #+#    #+#             */
/*   Updated: 2026/03/29 22:46:25 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_init_shell(t_shell *mini, char **ev)
{
	char	buf[4096];

	mini->env_bash = ev;
	mini->exit_status = 0;
	mini->env = init_env(ev);
	mini->cmds = NULL;
	mini->pwd_data.old_pwd = NULL;
	if (getcwd(buf, sizeof(buf)))
		mini->pwd_data.pwd = ft_strdup(buf);
	else
		mini->pwd_data.pwd = NULL;
}

int	main(int ac, char **ag, char **env)
{
	t_shell	mini;

	(void) ac;
	(void) ag;
	rl_catch_signals = 0;
	ft_init_shell(&mini, env);
	ft_init_sig_father();
	ft_loop(&mini);
	rl_clear_history();
}
