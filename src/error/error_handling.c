/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:57:10 by juan-her          #+#    #+#             */
/*   Updated: 2026/03/17 23:54:40 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_print_error_sintax_2(int message)
{
	if (message == 3)
	{
		ft_print_message(2, "Minishell: syntax error near ");
		ft_print_message(2, "unexpected token `|'\n");
	}
	else if (message == 4)
	{
		ft_print_message(2, "Minishell: syntax error near ");
		ft_print_message(2, "unexpected token `<'\n");
	}
	else if (message == 5)
	{
		ft_print_message(2, "Minishell: syntax error ");
		ft_print_message(2, "near unexpected token `>'\n");
	}
	else if (message == 6)
		ft_print_message(2, "Minishell: syntax error near unexpected token\n");
}

void	ft_print_error_sintax(int message)
{
	if (message == 0)
	{
		ft_print_message(2, "Minishell: syntax error near ");
		ft_print_message(2, "unexpected token 'newline'\n");
	}
	else if (message == 1)
	{
		ft_print_message(2, "Minishell: unexpected EOF while ");
		ft_print_message(2, "looking for matching `\"'\n");
	}
	else if (message == 2)
	{
		ft_print_message(2, "Minishell: unexpected EOF while");
		ft_print_message(2, " looking for matching `\''\n");
	}
	else
		ft_print_error_sintax_2(message);
}

void	ft_print_error_exec(int message, char *name)
{
	char	*msg;
	char	*finish_msg;

	finish_msg = NULL;
	msg = ft_strjoin("Minishell: ", name);
	if (!msg)
		return ;
	if (message == 0)
		finish_msg = ft_strjoin(msg, ": command not found\n");
	else if (message == 1)
		finish_msg = ft_strjoin(msg, ": Permission denied\n");
	else if (message == 2)
		finish_msg = ft_strjoin(msg, ": No such file or directory\n");
	else if (message == 3)
		finish_msg = ft_strjoin(msg, ": Is a directory\n");
	free(msg);
	if (finish_msg)
	{
		ft_print_message(2, finish_msg);
		free(finish_msg);
	}
}

static int	ft_files_ok(t_redir *redir)
{
	int	fd;

	fd = 0;
	if (redir->type == REDIR_IN)
	{
		if (access(redir->file, F_OK) != 0)
			return (ft_print_error_exec(2, redir->file), 0);
		if (access(redir->file, R_OK) != 0)
			return (ft_print_error_exec(1, redir->file), 0);
	}
	else if (redir->type == REDIR_APPEND)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (ft_print_error_exec(1, redir->file), 0);
		close(fd);
	}
	else if (redir->type == REDIR_OUT)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (ft_print_error_exec(1, redir->file), 0);
		close(fd);
	}
	return (1);
}

int	ft_check_files(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (!ft_files_ok(tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
