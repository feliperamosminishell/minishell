/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:44:25 by juan-her          #+#    #+#             */
/*   Updated: 2026/03/30 00:41:10 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile sig_atomic_t	g_who_sig = 0;

static void	ft_handle_sing(int sig)
{
	(void)sig;
	g_who_sig = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_init_sig_father(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = ft_handle_sing;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_init_sig_son(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ft_check_exit_statuc(t_shell **mini)
{
	int		status;
	pid_t	pid;

	pid = wait(&status);
	while (pid > 0)
	{
		if (WIFEXITED(status))
			(*mini)->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
			(*mini)->exit_status = 128 + WTERMSIG(status);
		}
		pid = wait(&status);
	}
}
