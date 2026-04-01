/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:48:32 by juan-her          #+#    #+#             */
/*   Updated: 2026/04/01 00:52:23 by juan-her         ###   ########.fr       */
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

static char	**ft_check_ev(char **env)
{
	char	*cwd;
	char	**ev;

	ev = env;
	if (*env == NULL)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (NULL);
		ev = (char **) malloc(4);
		if (!ev)
		{
			free(cwd);
			return (NULL);
		}
		ev[0] = ft_strjoin("PWD=", cwd);
		ev[1] = ft_strdup("SHLVL=1");
		ev[2] = ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
		ev[3] = NULL;
		free(cwd);
	}
	return (ev);
}

int	main(int ac, char **ag, char **env)
{
	t_shell	mini;
	char	**ev;

	(void) ac;
	(void) ag;
	ev = ft_check_ev(env);
	if (!ev)
		return (1);
	rl_catch_signals = 0;
	ft_init_shell(&mini, ev);
	ft_init_sig_father();
	ft_loop(&mini);
	rl_clear_history();
}
