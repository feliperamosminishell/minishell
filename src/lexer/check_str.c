/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:03:05 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/10 12:37:10 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int ft_is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static int ft_skip_spaces(const char *str, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

static int	ft_post_operator(const char *str, int *i)
{
	int next;

	next = 0;
	if (str[*i] == ';' || str[*i] == '&')
		return (0);
	if (str[*i] == '|' && str[*i + 1] == '|')
		return (0);
	if (ft_is_operator(str[*i]))
	{
		if ((str[*i] == '<' || str[*i] == '>') && str[*i] == str[*i + 1])
		{
			if (str[*i] == str[*i + 2])
				return (0);
			i++;
		}
		else if ((str[*i] == '<' && str[*i + 1] == '>') ||
				 (str[*i] == '>' && str[*i + 1] == '<'))
			return (0);
		next = ft_skip_spaces(str, *i + 1);
		if (ft_is_operator(str[next]))
			return (0);
		if (str[next] == '\0')
			return (0);
	}
	return (1);
}

static int	ft_last_check(const char *str, int quote_s, int quote_d, int i)
{
	if (quote_s || quote_d)
		return (0);
	i--;
	while (i >= 0 && (str[i] == ' ' || str[i] == '\t'))
		i--;
	if (i >= 0 && ft_is_operator(str[i]))
		return (0);
	return (1);
}

int ft_check_str(const char *str)
{
	int i;
	int quote_s;
	int quote_d;

	quote_s = 0;
	quote_d = 0;
	i = ft_skip_spaces(str, 0);
	if (str[i] == '|' || str[i] == ';' || str[i] == '&')
		return (0);
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
