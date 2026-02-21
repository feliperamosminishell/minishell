/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 04:13:58 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/18 16:20:23 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	ft_is_redir(en_token type)
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
