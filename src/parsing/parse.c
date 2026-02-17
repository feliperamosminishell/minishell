/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 03:03:59 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/17 22:48:30 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmd *ft_separate_token(t_token **token)
{
	t_args		*list_arg;
	t_cmd		*list_cmd;
	t_cmd		*cmd;

	list_arg = NULL;
	list_cmd = NULL;
	cmd = NULL;
	if (!*token)
		return (NULL);
	cmd = ft_new_cmd();
	if (!cmd)
		return (NULL);
	while (*token)
	{
		if (!ft_inst_data(&cmd, &list_cmd, &list_arg, token))
		{
			ft_free_cmds(&list_cmd);
            ft_free_args(&list_arg);
			if (cmd)
			{
				ft_free_redirs(&cmd->redirs);
				free(cmd);
			}
            return (NULL);    
		}
		*token = (*token)->next;
	}
	if (list_arg)
	{
		cmd->argv = ft_conv_args(&list_arg);
		ft_add_cmd(&list_cmd, cmd);
	}
	else
		ft_free_cmds(&cmd);
	return (list_cmd);
}

t_cmd *ft_parser(t_token **token)
{
	t_cmd *cmd;

	cmd = ft_separate_token(token);
	return (cmd);
}
