/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 19:59:57 by juan-her          #+#    #+#             */
/*   Updated: 2026/03/31 02:38:16 by juan-her         ###   ########.fr       */
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

static void	ft_child_io(int fd[2], int pv_p, t_cmd **cmd)
{
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
}

int	ft_exec_cmd_child(int fd[2], int pv_p, t_cmd **cmd, t_shell **mini)
{
	pid_t	pid;

	pid = fork();
	if (!ft_check_pid(pid))
		return (0);
	if (pid == 0)
	{
		ft_init_sig_son();
		ft_child_io(fd, pv_p, cmd);
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

void	ft_cleanup_cmds(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		cmd = cmd->next;
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
		if (ft_exec_builtin_solo(cmd, mini, prev_pipe) != 0)
			return ;
		if (cmd->next && pipe(fd) == -1)
			return ;
		if (!ft_execution(fd, prev_pipe, &cmd, mini))
		{
			if (prev_pipe != -1)
				close(prev_pipe);
			return ;
		}
		if (prev_pipe != -1)
			close(prev_pipe);
		ft_next_cmd(cmd, fd, &prev_pipe);
		cmd = cmd->next;
	}
	ft_exec_end(mini);
}
