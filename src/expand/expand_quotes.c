/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:46:10 by juan-her          #+#    #+#             */
/*   Updated: 2026/03/25 13:53:35 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_exp_in_quotes(const char *line, t_lexer *lx, char **val)
{
	char	*tmp;
	char	*exp;
	char	*join;

	if (line[lx->i] == '$')
	{
		exp = ft_expand_var(line, &lx->i, lx->last_status, lx ->env);
		join = ft_strjoin(*val, exp);
		free(*val);
		free(exp);
		*val = join;
	}
	else
	{
		tmp = ft_substr(line, lx->i, 1);
		join = ft_strjoin(*val, tmp);
		free(*val);
		free(tmp);
		*val = join;
		lx->i++;
	}
}

char	*ft_lexer_dq(const char *line, t_lexer *lx)
{
	char	*value;

	value = ft_strdup("");
	lx->i++;
	while (line[lx->i] && line[lx->i] != '\"')
		ft_exp_in_quotes(line, lx, &value);
	if (line[lx->i] == '\"')
		lx->i++;
	return (value);
}
