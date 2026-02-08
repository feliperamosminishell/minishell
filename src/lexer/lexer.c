/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:05:51 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/08 06:37:56 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (line[i] == '>' && line[i + 1] == '>')
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

t_token *ft_lexer(const char *line, int last_status)
{
	int     i;
	int     start;
	int     in[2];
	char    *expanded;
	t_token *list;

	i = 0;
	in[0] = 0;
	in[1] = 0;
	list = NULL;
	if (!ft_check_str(line))
		return (NULL);
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!line[i])
			break;
		start = i;
		if (!in[0] && !in[1] && (line[i] == '|' || line[i] == '<'
				|| line[i] == '>'))
			i = ft_handle_operator(&list, line, i);
		else
		{
			while (line[i] && (!ft_isspace(line[i]) || in[0] || in[1])
				&& !(line[i] == '|' || line[i] == '<' || line[i] == '>'))
			{
				if (line[i] == '\'' && !in[1])
					in[0] = !in[0];
				else if (line[i] == '\"' && !in[0])
					in[1] = !in[1];
				else if (line[i] == '$' && !in[0])
				{
					if (i > start)
						ft_create_word_token(&list, line, start, i);
					expanded = ft_expand_var(line, &i, last_status);
					ft_lstadd_token(&list, ft_new_token(WORD, expanded));
					start = i;
					continue;
				}
				i++;
			}
			ft_create_word_token(&list, line, start, i);
		}
	}
	return (list);
}
