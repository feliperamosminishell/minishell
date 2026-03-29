/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 04:13:58 by juan-her          #+#    #+#             */
/*   Updated: 2026/03/30 00:41:39 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	ft_is_redir(t_en_token type)
{
	if (type == REDIR_IN || type == REDIR_OUT
		|| type == REDIR_APPEND || type == HEREDOC)
		return (1);
	return (0);
}

int	ft_skip_spaces(const char *str, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

void	ft_next_operator(char c, int type)
{
	if (c == '|' && type)
		ft_print_error_sintax(3);
	else if (c == '<' && type)
		ft_print_error_sintax(4);
	else if (c == '>' && type)
		ft_print_error_sintax(5);
	else
		ft_print_error_sintax(0);
}

int	ft_pipe_followed_by_redir(const char *str, int i)
{
	int	next;

	if (str[i] != '|')
		return (1);
	next = ft_skip_spaces(str, i + 1);
	if (str[next] == '<' || str[next] == '>')
		return (ft_print_error_sintax(0), 0);
	return (1);
}
