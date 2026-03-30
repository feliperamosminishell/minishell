/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 11:49:45 by juan-her          #+#    #+#             */
/*   Updated: 2026/03/30 19:40:15 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_read_stdin(char *limiter, t_shell **mini, int quotes, int fd)
{
	char	*line;

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
		if (quotes)
			write(fd, line, ft_strlen(line));
		else
			ft_write_pipe(line, (*mini)->exit_status, fd, (*mini)->env);
		write(fd, "\n", 1);
		free(line);
	}
}

static int	ft_heredoc_interrupted(int fd0, t_shell **mini)
{
	close(fd0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	(*mini)->exit_status = 130;
	return (-1);
}

static void	ft_heredoc_child(char *limiter, t_shell **mini, int quotes, int *fd)
{
	signal(SIGINT, SIG_DFL);
	close(fd[0]);
	ft_read_stdin(limiter, mini, quotes, fd[1]);
	close(fd[1]);
	exit(0);
}

int	ft_handle_heredoc(char *limiter, t_shell **mini, int quotes)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
		ft_heredoc_child(limiter, mini, quotes, fd);
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(fd[0]);
		return (ft_heredoc_interrupted(-1, mini));
	}
	return (fd[0]);
}

void	ft_close_all_heredocs(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->fd_in != STDIN_FILENO)
		{
			close(cmd->fd_in);
			cmd->fd_in = STDIN_FILENO;
		}
		cmd = cmd->next;
	}
}
