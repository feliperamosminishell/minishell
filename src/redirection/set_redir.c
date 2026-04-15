/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 11:49:45 by juan-her          #+#    #+#             */
/*   Updated: 2026/04/15 07:29:44 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_limiter(char *line, char *limiter)
{
	if (!line || !limiter)
		return (0);
	return (ft_strlen(line) == ft_strlen(limiter)
		&& ft_strncmp(line, limiter, ft_strlen(limiter)+1) == 0);
}

static void	ft_read_stdin(char *limiter, t_shell **mini, int quotes, int fd)
{
	char	*line;
	size_t	len;

	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (is_limiter(line, limiter))
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

static int	ft_heredoc_interrupted(t_shell **mini)
{
	ft_close_all_heredocs((*mini)->cmds);
	write(1, "^C\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	(*mini)->exit_status = 130;
	return (-1);
}

static void	ft_heredoc_child(char *limiter, t_shell **mini, int quotes, int *fd)
{
	int	write_fd;

	write_fd = fd[1];
	close(fd[0]);
	close(fd[1]);
	signal(SIGINT, ft_heredoc_sigint);
	ft_read_stdin(limiter, mini, quotes, write_fd);
	ft_free_shell(*mini);
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
		return (ft_heredoc_interrupted(mini));
	}
	return (fd[0]);
}

void	ft_close_all_heredocs(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->fd_in != STDIN_FILENO && cmd->fd_in != -1)
		{
			close(cmd->fd_in);
			cmd->fd_in = STDIN_FILENO;
		}
		cmd = cmd->next;
	}
}
