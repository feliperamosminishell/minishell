/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:05:51 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/17 15:18:21 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int ft_handle_operator(t_token **list, const char *line, int i)
{
	if (line[i] == '<' && line[i + 1] == '<')
	{
		ft_lstadd_token(list, ft_new_token(HEREDOC, ft_strdup("<<")));
		return (i + 2);
	}
	if (line[i] == '>'  && line[i + 1] == '>')
	{
		ft_lstadd_token(list, ft_new_token(REDIR_APPEND, ft_strdup(">>")));
		return (i + 2);
	}
	if (line[i] == '<')
		ft_lstadd_token(list, ft_new_token(REDIR_IN, ft_strdup("<")));
	else if (line[i] == '>')
		ft_lstadd_token(list, ft_new_token(REDIR_OUT, ft_strdup(">")));
	else if (line[i] == '|')
		ft_lstadd_token(list, ft_new_token(PIPE, ft_strdup("|")));
	return (i + 1);
}

static char *ft_lexer_dq(const char *line, t_lexer *lx)
{
	char *value;
	char *tmp;
	char *exp;
	char *join;

	value = ft_strdup("");
	lx->i++; 
	while (line[lx->i] && line[lx->i] != '\"')
	{
		if (line[lx->i] == '$')
		{
			exp = ft_expand_var(line, &lx->i, lx->last_status);
			join = ft_strjoin(value, exp);
			free(value);
			free(exp);
			value = join;
		}
		else
		{
			tmp = ft_substr(line, lx->i, 1);
			join = ft_strjoin(value, tmp);
			free(value);
			free(tmp);
			value = join;
			lx->i++;
		}
	}
	if (line[lx->i] == '"')
		lx->i++;
	return (value);
}

static void ft_init_lexer(t_lexer *lexer, int last_status)
{
	lexer->i = 0;
	lexer->in_s = 0;
	lexer->in_d = 0;
	lexer->start = 0;
	lexer->list = NULL;
	lexer->last_status = last_status;
}

void ft_handle_word(const char *line, t_lexer *lx)
{
	char *exp;
	char *value;
	char *join;
	char *tmp;

	value = ft_strdup("");
	while (line[lx->i] && !ft_is_operator(line[lx->i]) &&(!ft_isspace(line[lx->i]) || lx->in_s))
	{
		if (line[lx->i] == '\'' )
		{
			lx->in_s = !lx->in_s;
			lx->i++;
		}
		else if (line[lx->i] == '\"' && !lx->in_s)
		{
			exp = ft_lexer_dq(line, lx);
			join = ft_strjoin(value, exp);
			free(value);
			free(exp);
			value = join;
		}
		else if (line[lx->i] == '$' && !lx->in_s)
		{
			exp = ft_expand_var(line, &lx->i, lx->last_status);
			join = ft_strjoin(value, exp);
			free(value);
			free(exp);
			value = join;
		}
		else
		{
			tmp = ft_substr(line, lx->i, 1);
			join = ft_strjoin(value, tmp);
			free(value);
			free(tmp);
			value = join;
			lx->i++;
		}
	}
	if (value && value[0])
		ft_lstadd_token(&lx->list, ft_new_token(WORD, value));
	else
		free(value);
}


t_token *ft_lexer(const char *line, int last_status)
{
	t_lexer lx;
	
	ft_init_lexer(&lx, last_status);
	if (!ft_check_str(line))
		return (NULL);
	while (line[lx.i])
	{
		while (ft_isspace(line[lx.i]))
			lx.i++;
		if (!line[lx.i])
			break;
		lx.start = lx.i;
		if (!lx.in_s && ft_is_operator(line[lx.i]))
			lx.i = ft_handle_operator(&(lx.list), line, lx.i);
		else
			ft_handle_word(line, &lx);
	}
	return (lx.list);
}
