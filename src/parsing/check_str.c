/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 21:21:46 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/01 23:19:45 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_check_str(char *str)
{
    int i;
    int j;
    int ext;
    int in_single;
    int in_double;

    i = 0;
    ext = 0;
    in_double = 0;
    in_single = 0;
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    if (str[i] == '|')
        return (0);
    while (str[i])
    {
        if (str[i] == '\'' && !in_double)
            in_single = 1;
        else if (str[i] == '\"' && !in_single)
            in_double = 1;
        else if (!in_single && !in_double)
        {
            if (str[i] == ';')
                return (0);
            if (str[i] == '&')
                return (0);
            if ((str[i] == '<' || str[i] == '>' || str[i] == '|') && ext)
                return (0);
            if (str[i] == '|')
            {
                j = i + 1;
                while (str[j] == ' ' || str[j] == '\t')
                    j++;
                if (str[j] == '|' || str[j] == '\0')
                    return (0);
                ext = 1;
            }
            else if (str[i] == '<')
            {
                if (str[i + 1] == '<')
                    i++;
                else if (str[i + 1] == '>' || str[i + 1] == '|')
                    return (0);
                ext = 1;
            }
            else if (str[i] == '>')
            {
                if (str[i + 1] == '>')
                    i++;
                else if (str[i + 1] == '<' || str[i + 1] == '|')
                    return (0);
                ext = 1;
            }
            else if ((str[j] != ' ' || str[j] != '\t') && ext)
                ext = 0;
        }
        if (str[i] == '\'' && in_single)
            in_single = 0;
        else if (str[i] == '\"' && in_double)
            in_double = 0;
        i++;
    }
    if (in_single || in_double)
        return (0);
    if (ext)
        return (0);
    i--;
    while (i >= 0 && (str[i] == ' ' || str[i] == '\t'))
        i--;
    if (str[i] == '|')
        return (0);
    return (1);
}