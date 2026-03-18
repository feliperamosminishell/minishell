/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:01:04 by juan-her          #+#    #+#             */
/*   Updated: 2026/03/16 19:49:16 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_double_q(const char *line, t_lexer *lx, char **vl)
{
	char	*exp;
	char	*join;

	exp = ft_lexer_dq(line, lx);
	join = ft_strjoin(*vl, exp);
	free(*vl);
	free(exp);
	*vl = join;
}

static void	ft_globlal(const char *line, t_lexer *lx, char **vl)
{
	char	*exp;
	char	*join;

	exp = ft_expand_var(line, &lx->i, lx->last_status);
	join = ft_strjoin(*vl, exp);
	free(*vl);
	free(exp);
	*vl = join;
}

static void	ft_word(const char *line, t_lexer *lx, char **vl)
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

static void	ft_search_line(const char *line, t_lexer *lx, int *quotes, char **value)
{
	if (line[lx->i] == '\'' )
	{
		lx->in_s = !lx->in_s;
		lx->i++;
		*quotes = 1;
	}
	else if (line[lx->i] == '\"' && !lx->in_s)	
	{
		ft_double_q(line, lx, value);
		*quotes = 1;
	}
	else if (line[lx->i] == '$' && !lx->in_s)
		ft_globlal(line, lx, value);
	else
		ft_word(line, lx, value);
}

void	ft_handle_word(const char *line, t_lexer *lx)
{
	char	*value;
	int		quotes;

	quotes = 0;
	value = ft_strdup("");
	while (line[lx->i] && !ft_is_operator(line[lx->i])
		&& (!ft_isspace(line[lx->i]) || lx->in_s))
		ft_search_line(line, lx, &quotes, &value);
	if (value && value[0])
		ft_lstadd_token(&lx->list, ft_new_token(WORD, value, quotes));
	else
		free(value);
}
