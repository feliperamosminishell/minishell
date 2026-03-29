/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:05:51 by juan-her          #+#    #+#             */
/*   Updated: 2026/03/29 22:52:23 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_handle_operator(t_token **list, const char *line, int i)
{
	if (line[i] == '<' && line[i + 1] == '<')
	{
		ft_lstadd_token(list, ft_new_token(HEREDOC, ft_strdup("<<"), 0));
		return (i + 2);
	}
	if (line[i] == '>' && line[i + 1] == '>')
	{
		ft_lstadd_token(list, ft_new_token(REDIR_APPEND, ft_strdup(">>"), 0));
		return (i + 2);
	}
	if (line[i] == '<')
		ft_lstadd_token(list, ft_new_token(REDIR_IN, ft_strdup("<"), 0));
	else if (line[i] == '>')
		ft_lstadd_token(list, ft_new_token(REDIR_OUT, ft_strdup(">"), 0));
	else if (line[i] == '|')
		ft_lstadd_token(list, ft_new_token(PIPE, ft_strdup("|"), 0));
	return (i + 1);
}

static void	ft_init_lexer(t_lexer *lexer, int last_status, t_shell **mini)
{
	lexer->i = 0;
	lexer->in_s = 0;
	lexer->in_d = 0;
	lexer->start = 0;
	lexer->list = NULL;
	lexer->last_status = last_status;
	lexer->env = (*mini)->env;
}

static void	ft_process_token(const char *line, t_lexer *lx)
{
	if (!lx->in_s && ft_is_operator(line[lx->i]))
	{
		if (line[lx->i] == '<' && line[lx->i + 1] == '<')
			lx->after_heredoc = 1;
		lx->i = ft_handle_operator(&(lx->list), line, lx->i);
	}
	else
	{
		ft_handle_word(line, lx);
		lx->after_heredoc = 0;
	}
}

static void	ft_lex_loop(const char *line, t_lexer *lx)
{
	while (line[lx->i])
	{
		while (ft_isspace(line[lx->i]))
			lx->i++;
		if (!line[lx->i])
			break ;
		lx->start = lx->i;
		ft_process_token(line, lx);
	}
}

t_token	*ft_lexer(const char *line, int last_status, t_shell **mini)
{
	t_lexer	lx;

	ft_init_lexer(&lx, last_status, mini);
	if (!ft_check_str(line))
	{
		(*mini)->exit_status = 127;
		return (NULL);
	}
	ft_lex_loop(line, &lx);
	return (lx.list);
}
