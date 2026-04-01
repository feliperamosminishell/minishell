/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 04:28:45 by juan-her          #+#    #+#             */
/*   Updated: 2026/03/31 15:30:12 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_globlal(const char *line, t_lexer *lx, char **vl)
{
	char	*exp;
	char	*join;

	exp = ft_expand_var(line, &lx->i, lx->last_status, lx->env);
	join = ft_strjoin(*vl, exp);
	free(*vl);
	free(exp);
	*vl = join;
}

void	ft_word(const char *line, t_lexer *lx, char **vl)
{
	char	*tmp;
	char	*join;

	tmp = ft_substr(line, lx->i, 1);
	join = ft_strjoin(*vl, tmp);
	free(*vl);
	free(tmp);
	*vl = join;
	lx->i++;
}
