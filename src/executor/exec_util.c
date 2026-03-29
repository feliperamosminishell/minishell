/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 11:35:39 by goramos-          #+#    #+#             */
/*   Updated: 2026/03/27 11:40:54 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exec_end(t_shell **mini)
{
	ft_check_exit_statuc(mini);
	ft_init_sig_father();
}

int	ft_execution(int fd[2], int pv_p, t_cmd **cmd, t_shell **mini)
{
	if (!ft_prepare_redirection(*cmd, mini))
		return (0);
	if (!ft_exec_cmd_child(fd, pv_p, cmd, mini))
		return (0);
	return (1);
}

void	ft_next_cmd(t_cmd *cmd, int *fd, int *prev_pipe)
{
	if (cmd->next)
	{
		close(fd[1]);
		*prev_pipe = fd[0];
	}
}

int	ft_exec_builtin_solo(t_cmd *cmd, t_shell **mini, int prev_pipe)
{
	if (cmd->next || prev_pipe != -1 || !cmd->argv || !cmd->argv[0])
		return (0);
	if (!ft_is_builtin(cmd->argv[0]))
		return (0);
	if (!ft_prepare_redirection(cmd, mini))
		return (-1);
	ft_apply_redirections(cmd);
	ft_exc_built(mini, cmd);
	return (1);
}
