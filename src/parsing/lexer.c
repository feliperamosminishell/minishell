/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 01:14:13 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/04 16:21:55 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token *ft_lexer(const char *line)
{
    int i = 0;
    int start = -1;
    int in_single = 0;
    int in_double = 0;
    char *tmp;
    t_token *list = NULL;
    t_token *node;

    if (!ft_check_str((char *)line))
        return (NULL);

    while (line[i])
    {
        if (line[i] == '\'' && !in_double)
        {
            if (!in_single)
                start = i + 1;
            else
            {
                node = ft_new_token(SINGLEQ,
                        ft_substr(line, start, (size_t)i - start));
                ft_token_add_back(&list, node);
            }
            in_single = 1;
        }
        else if (line[i] == '\"' && !in_single)
        {
            if (!in_double)
                start = i + 1;
            else
            {
                node = ft_new_token(DOUBLEQ,
                        ft_substr(line, start, i - start));
                ft_token_add_back(&list, node);
            }
            in_double = 1;
        }
        else if (!in_single && !in_double)
        {
            if (ft_isspace(line[i]) && start != -1)
            {
                node = ft_new_token(WORD,
                        ft_substr(line, start, i - start));
                ft_token_add_back(&list, node);
                start = -1;
            }
            else if (line[i] == '|')
            {
                if (start != -1)
                {
                    node = ft_new_token(WORD,
                            ft_substr(line, start, i - start));
                    ft_token_add_back(&list, node);
                    start = -1;
                }
                node = ft_new_token(PIPE, ft_strdup("|"));
                ft_token_add_back(&list, node);
            }
            else if (line[i] == '<' && line[i + 1] == '<')
            {
                if (start != -1)
                {
                    node = ft_new_token(WORD,
                            ft_substr(line, start, i - start));
                    ft_token_add_back(&list, node);
                    start = -1;
                }
                node = ft_new_token(HEREDOC, ft_strdup("<<"));
                ft_token_add_back(&list, node);
                i++;
            }
            else if (line[i] == '>' && line[i + 1] == '>')
            {
                if (start != -1)
                {
                    node = ft_new_token(WORD,
                            ft_substr(line, start, i - start));
                    ft_token_add_back(&list, node);
                    start = -1;
                }
                node = ft_new_token(REDIR_APPEND, ft_strdup(">>"));
                ft_token_add_back(&list, node);
                i++;
            }
            else if (line[i] == '<')
            {
                if (start != -1)
                {
                    node = ft_new_token(WORD,
                            ft_substr(line, start, i - start));
                    ft_token_add_back(&list, node);
                    start = -1;
                }
                node = ft_new_token(REDIR_IN, ft_strdup("<"));
                ft_token_add_back(&list, node);
            }
            else if (line[i] == '>')
            {
                if (start != -1)
                {
                    node = ft_new_token(WORD,
                            ft_substr(line, start, i - start));
                    ft_token_add_back(&list, node);
                    start = -1;
                }
                node = ft_new_token(REDIR_OUT, ft_strdup(">"));
                ft_token_add_back(&list, node);
            }
            else if (start == -1)
                start = i;
        }
        if (line[i] == '$' && !in_single)
        {
            if (start != -1)
            {
                node = ft_new_token(WORD,
                        ft_substr(line, start, i - start));
                ft_token_add_back(&list, node);
            }
            tmp = expand_var(line, &i);
            node = ft_new_token(WORD, tmp);
            ft_token_add_back(&list, node);
            start = -1;
            continue;
        }
        i++;
    }
    if (start != -1)
    {
        node = ft_new_token(WORD,
                ft_substr(line, start, i - start));
        ft_token_add_back(&list, node);
    }
    return (list);
}
