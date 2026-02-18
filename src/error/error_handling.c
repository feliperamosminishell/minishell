/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:57:10 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/18 15:56:41 by juan-her         ###   ########.fr       */
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
