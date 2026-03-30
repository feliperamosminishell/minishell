/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 22:54:34 by goramos-          #+#    #+#             */
/*   Updated: 2026/03/30 19:40:45 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_set_fd(t_redir *rd_tmp, t_shell **mini)
{
	int	fd;

	fd = 0;
	if (rd_tmp->type == HEREDOC)
	{
		fd = ft_handle_heredoc(rd_tmp->file, mini, rd_tmp->quotes);
		ft_init_sig_father();
	}
	else if (rd_tmp->type == REDIR_IN)
		fd = open(rd_tmp->file, O_RDONLY);
	else if (rd_tmp->type == REDIR_OUT)
		fd = open(rd_tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (rd_tmp->type == REDIR_APPEND)
		fd = open(rd_tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

int	ft_prepare_redirection(t_cmd *cmd, t_shell **mini)
{
	int		fd;
	t_redir	*rd_tmp;

	rd_tmp = cmd->redirs;
	while (rd_tmp)
	{
		fd = ft_set_fd(rd_tmp, mini);
		if (rd_tmp->type == HEREDOC || rd_tmp->type == REDIR_IN)
		{
			if (cmd->fd_in != STDIN_FILENO)
				close(cmd->fd_in);
			cmd->fd_in = fd;
		}
		else
		{
			if (cmd->fd_out != STDOUT_FILENO)
				close(cmd->fd_out);
			cmd->fd_out = fd;
		}
		rd_tmp = rd_tmp->next;
	}
	return (1);
}

void	ft_apply_redirections(t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
}
