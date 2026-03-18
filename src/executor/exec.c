/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 19:59:57 by juan-her          #+#    #+#             */
/*   Updated: 2026/03/18 23:17:23 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_check_pid(pid_t pid)
{
	if (pid == -1)
	{
		perror("fork");
		return (0);
	}
	return (1);
}

static int	ft_exec_cmd_child(int fd[2], int pv_p, t_cmd **cmd, t_shell **mini)
{
	pid_t	pid;

	pid = fork();
	if (!ft_check_pid(pid))
		return (0);
	if (pid == 0)
	{
		ft_init_sig_son();
		if (pv_p != -1)
		{
			dup2(pv_p, STDIN_FILENO);
			close(pv_p);
		}
		if ((*cmd)->next)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
		}
		ft_apply_redirections(*cmd);
		if ((*cmd)->argv && (*cmd)->argv[0] && ft_is_builtin((*cmd)->argv[0]))
		{
			ft_exc_built(mini, *cmd);
			exit((*mini)->exit_status);
		}
		else
		{
			ft_execute((*cmd)->argv, (*mini)->env_bash);
			exit(1);
		}
	}
	return (1);
}

static int	ft_execution(int fd[2], int pv_p, t_cmd **cmd, t_shell **mini)
{
	if (!ft_prepare_redirection(*cmd, mini))
		return (0);
	if (!ft_exec_cmd_child(fd, pv_p, cmd, mini))
		return (0);
	return (1);
}

static void	ft_next_cmd(t_cmd *cmd, int *fd, int *prev_pipe)
{
	if (cmd->next)
	{
		close(fd[1]);
		*prev_pipe = fd[0];
	}
}

void	ft_exec(t_shell **mini)
{
	t_cmd	*cmd;
	int		fd[2];
	int		prev_pipe;

	signal(SIGINT, SIG_IGN);
	cmd = (*mini)->cmds;
	prev_pipe = -1;
	while (cmd)
	{
		if (!cmd->next && prev_pipe == -1 && cmd->argv && cmd->argv[0] && ft_is_builtin(cmd->argv[0]))
		{
			ft_apply_redirections(cmd);
			ft_exc_built(mini, cmd);
			return ;
		}
		if (cmd->next)
		{
			if (pipe(fd) == -1)
				return ;
		}
		if (!ft_execution(fd, prev_pipe, &cmd, mini))
			return ;
		if (prev_pipe != -1)
			close(prev_pipe);
		ft_next_cmd(cmd, fd, &prev_pipe);
		cmd = cmd->next;
	}
	ft_check_exit_statuc(mini);
	ft_init_sig_father();
}
