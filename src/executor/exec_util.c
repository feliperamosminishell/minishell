/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 11:35:39 by goramos-          #+#    #+#             */
/*   Updated: 2026/04/15 05:01:10 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exec_end(t_shell **mini)
{
	ft_check_exit_statuc(mini);
	ft_init_sig_father();
}

static void	ft_close_cmd_fds(t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		close(cmd->fd_in);
		cmd->fd_in = STDIN_FILENO;
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		close(cmd->fd_out);
		cmd->fd_out = STDOUT_FILENO;
	}
}

int	ft_execution(int fd[2], int pv_p, t_cmd **cmd, t_shell **mini)
{
	if (!ft_prepare_redirection(*cmd, mini))
		return (0);
	if (!(*cmd)->argv || !(*cmd)->argv[0])
		return (1);
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
	(*mini)->stdin_backup = dup(STDIN_FILENO);
	(*mini)->stdout_backup = dup(STDOUT_FILENO);
	ft_apply_redirections(cmd);
	ft_exc_built(mini, cmd);
	dup2((*mini)->stdin_backup, STDIN_FILENO);
	dup2((*mini)->stdout_backup, STDOUT_FILENO);
	close((*mini)->stdin_backup);
	close((*mini)->stdout_backup);
	ft_close_cmd_fds(cmd);
	ft_check_exit_statuc(mini);
	ft_init_sig_father();
	return (1);
}
