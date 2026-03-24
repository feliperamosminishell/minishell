/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:03:05 by juan-her          #+#    #+#             */
/*   Updated: 2026/03/24 13:08:20 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_error_check_2(const char *str, int *i)
{
	if (str[*i] == '<' && str[*i] == str[*i + 1])
	{
		if (str[*i] == str[*i + 2])
			return (ft_print_error_sintax(4), 0);
		(*i)++;
	}
	else if (str[*i] == '>' && str[*i] == str[*i + 1])
	{
		if (str[*i] == str[*i + 2])
			return (ft_print_error_sintax(5), 0);
		(*i)++;
	}
	else if ((str[*i] == '<' && str[*i + 1] == '>')
		|| (str[*i] == '>' && str[*i + 1] == '<'))
		return (ft_print_error_sintax(0), 0);
	return (1);
}

static int	ft_error_check(const char *str, int *i)
{
	int	next;

	next = 0;
	if (ft_is_operator(str[*i]))
	{
		if (!ft_error_check_2(str, i))
			return (0);
		next = ft_skip_spaces(str, *i + 1);
		if (ft_is_operator(str[next]))
			return (ft_next_operator(str[next], 1), 0);
		if (str[next] == '\0')
			return (ft_next_operator(str[next], 0), 0);
	}
	return (1);
}

static int	ft_post_operator(const char *str, int *i)
{
	if (str[*i] == ';' || str[*i] == '&')
		return (ft_print_error_sintax(6), 0);
	if (str[*i] == '|' && str[*i + 1] == '|')
		return (ft_print_error_sintax(3), 0);
	if (!ft_pipe_followed_by_redir(str, *i))
		return (0);
	if (!ft_error_check(str, i))
		return (0);
	return (1);
}

static int	ft_last_check(const char *str, int quote_s, int quote_d, int i)
{
	if (quote_s)
		return (ft_print_error_sintax(2), 0);
	else if (quote_d)
		return (ft_print_error_sintax(1), 0);
	i--;
	while (i >= 0 && (str[i] == ' ' || str[i] == '\t'))
		i--;
	if (i >= 0 && ft_is_operator(str[i]))
		return (ft_next_operator(str[i], 1), 0);
	return (1);
}

int	ft_check_str(const char *str)
{
	int	i;
	int	quote_s;
	int	quote_d;

	quote_s = 0;
	quote_d = 0;
	i = ft_skip_spaces(str, 0);
	if (str[i] == '|' || str[i] == ';' || str[i] == '&')
		return (ft_print_error_sintax(6), 0);
	while (str[i])
	{
		if (str[i] == '\'' && !quote_d)
			quote_s = !quote_s;
		else if (str[i] == '\"' && !quote_s)
			quote_d = !quote_d;
		else if (!quote_s && !quote_d)
		{
			if (!ft_post_operator(str, &i))
				return (0);
		}
		i++;
	}
	if (!ft_last_check(str, quote_s, quote_d, i))
		return (0);
	return (1);
}
