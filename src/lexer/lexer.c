/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:05:51 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/13 21:15:29 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void ft_create_word_token(t_token **list, const char *line, int start, int end)
{
	char *value;

	if (end <= start)
		return;
	value = ft_substr(line, start, end - start);
	ft_lstadd_token(list, ft_new_token(WORD, value));
}

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
    char *expanded;

    while (line[lx->i]
        && (!ft_isspace(line[lx->i]) || lx->in_s || lx->in_d)
        && !ft_is_operator(line[lx->i]))
    {
        if (line[lx->i] == '\'' && !lx->in_d)
            lx->in_s = !lx->in_s;
        else if (line[lx->i] == '\"' && !lx->in_s)
            lx->in_d = !lx->in_d;
        else if (line[lx->i] == '$' && !lx->in_s)
        {
            if (lx->i > lx->start)
                ft_create_word_token(&lx->list, line, lx->start, lx->i);
            expanded = ft_expand_var(line, &lx->i, lx->last_status);
			if (expanded && expanded[0])
            	ft_lstadd_token(&lx->list, ft_new_token(WORD, expanded));
            lx->start = lx->i;
            continue;
        }
        lx->i++;
    }
    if (lx->i > lx->start)
        ft_create_word_token(&lx->list, line, lx->start, lx->i);
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
		if (!lx.in_s && !lx.in_d && ft_is_operator(line[lx.i]))
			lx.i = ft_handle_operator(&(lx.list), line, lx.i);
		else
			ft_handle_word(line, &lx);
	}
	return (lx.list);
}
