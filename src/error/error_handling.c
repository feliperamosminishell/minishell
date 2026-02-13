/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:57:10 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/12 15:22:03 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void ft_print_error_sintax(int message)
{
    //ls | o echo hola > <
    if (message == 0)
        ft_print_message(2, "Minishell: syntax error near unexpected token 'newline'\n");
    else if (message == 1)
        ft_print_message(2, "Minishell: unexpected EOF while looking for matching `\"'\n");
    else if (message == 2)
        ft_print_message(2, "Minishell: unexpected EOF while looking for matching `\''\n");
    //ls || wc o ls | | wc, los siguientes los que empiezen con su cada cueal
    else if (message == 3)
        ft_print_message(2, "Minishell: syntax error near unexpected token `|'\n");
    else if (message == 4)
        ft_print_message(2, "Minishell: syntax error near unexpected token `<'\n");
    else if (message == 5)
        ft_print_message(2, "Minishell: syntax error near unexpected token `>'\n");
    //No estoy muy seguro pero para los errores de sintaxis
    else if (message == 6)
        ft_print_message(2, "Minishell: syntax error near unexpected token\n");
}

void ft_print_error_exec(int message, char *name)
{
    char *msg;
    char *finish_msg;
    
    msg = ft_strjoin("Minishell: ", name);
    if (!msg)
        return ;
    //comando no encontrado
    if (message == 0)
        finish_msg = ft_strjoin(msg, ": command not found\n");
    //Comando o archivo sin permisos o error de redireccion
    else if (message == 1)
        finish_msg = ft_strjoin(msg, ": Permission denied\n");
    //Si el archivo no existe
    else if (message == 2)
        finish_msg = ft_strjoin(msg, ": No such file or directory\n");
    //directorio como comando
    else if (message == 3)
        finish_msg = ft_strjoin(msg, ": Is a directory\n");
    free(msg);
    if (finish_msg)
    {
        ft_print_message(2, finish_msg);
        free(finish_msg);
    }
}

