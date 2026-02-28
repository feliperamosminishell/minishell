/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 11:49:45 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/28 20:32:47 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	ft_handle_heredoc(char *limiter)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}

static int	ft_set_fd(t_redir *rd_tmp)
{
	int	fd;

	if (rd_tmp->type == HEREDOC)
		fd = ft_handle_heredoc(rd_tmp->file);
	else if (rd_tmp->type == REDIR_IN)
		fd = open(rd_tmp->file, O_RDONLY);
	else if (rd_tmp->type == REDIR_OUT)
		fd = open(rd_tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (rd_tmp->type == REDIR_APPEND)
		fd = open(rd_tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

int	ft_prepare_redirection(t_cmd *cmd)
{
	int		fd;
	t_redir	*rd_tmp;

	rd_tmp = cmd->redirs;
	while (rd_tmp)
	{
		fd = ft_set_fd(rd_tmp);
		if (fd < 0)
			return (0);
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
