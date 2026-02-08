/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cnt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 02:55:14 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/08 06:20:56 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_add_args(t_args **list, char *value)
{
    t_args *new;
    t_args *tmp;

    new = ft_new_args(ft_strdup(value));
    if (!new)
        return (-1);
    if (!*list)
        *list = new;
    else
    {
        tmp = *list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new; 
    }
    return (0);
}

int ft_add_redir (t_redir **list, en_token type, char *file)
{
    t_redir *new;
    t_redir *tmp;

    new = ft_new_redir(ft_strdup(file), type);
    if (!new)
        return (-1);
    if (!*list)
        *list = new;
    else
    {
        tmp = *list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
    return (0);
}

char **ft_conv_args(t_args **ag)
{
    int count;
    int i;
    char    **args;
    t_args *next;
    t_args *tmp;

    i = 0;
    count = 0;
    tmp = *ag;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    args = ft_calloc((count + 1), sizeof(char *));
    if (!args)
        return (NULL);
    tmp = *ag;
    while (tmp)
    {
        args[i++] = tmp->ag;
        next = tmp->next;
        free(tmp);
        tmp = next;    
    }
    *ag = NULL;
    return (args);
}

void ft_add_cmd(t_cmd **list, t_cmd *new)
{
    t_cmd *tmp;
    
    tmp = *list;
    if (!*list)
        *list = new;
    else
    {
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}