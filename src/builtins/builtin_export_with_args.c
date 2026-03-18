/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_with_args.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:58:03 by goramos-          #+#    #+#             */
/*   Updated: 2026/03/18 00:07:42 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void export_one_arg(t_shell *shell, char *arg)
{
    char    *key;
    char    *val;
    t_env   *node;
    int     has_value;  // ← añadir esto

    key = get_key(arg);
    if (!is_valid_id(key))
    {
        ft_putstr_fd("minishell: export: '", 2);
        ft_putstr_fd(arg, 2);
        ft_putstr_fd("': not a valid identifier\n", 2);
        free(key);
        shell->exit_status = 1;
        return ;
    }
    has_value = (ft_strchr(arg, '=') != NULL);  // ← ¿tiene '='?
    val = get_value(arg);
    node = env_find(shell->env, key);
    if (node)
    {
        if (has_value)          // solo actualizar si hay '='
            env_update(node, val);
    }
    else
        add_back_env(&shell->env, create_env_node(key, val));
    free(key);
    free(val);
}

void    builtin_export_with_args(t_shell *shell, char **args)
{
    int i;

    i = 1;
    while (args[i])
    {
        export_one_arg(shell, args[i]);
        i++;
    }
}