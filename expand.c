/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 01:53:29 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/02 01:57:15 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_var(const char *line, int *i)
{
    int start;
    char *var;
    char *value;

    (*i)++;
    start = *i;
    while (ft_isalnum(line[*i]) || line[*i] == '_')
        (*i)++;
    var = ft_substr(line, start, *i - start);
    value = getenv(var);
    free(var);
    if (!value)
        return (ft_strdup(""));
    return (ft_strdup(value));
}
