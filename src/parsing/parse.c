/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 03:03:59 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/10 12:59:33 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd *ft_parser(t_token **token)
{
	t_args		*list_arg;
	t_cmd		*list_cmd;
	t_cmd		*cmd;
	en_token	type;

	list_arg = NULL;
	list_cmd = NULL;
	cmd = ft_new_cmd();
	if (!cmd || !*token)
		return (NULL);
	while (*token)
	{
		if ((*token)->type == WORD)
			ft_add_args(&list_arg, (*token)->value);
		else if ((*token)->type == REDIR_IN
			|| (*token)->type == REDIR_OUT
			|| (*token)->type == REDIR_APPEND
			|| (*token)->type == HEREDOC)
		{
			type = (*token)->type;
			*token = (*token)->next;
			if (!*token || (*token)->type != WORD)
			{
				ft_free_args(&list_arg);
				ft_free_cmds(&cmd);
				ft_free_cmds(&list_cmd);
				return (NULL);
			}
			ft_add_redir(&cmd->redirs, type, (*token)->value);
		}
		else if ((*token)->type == PIPE)
		{
			cmd->argv = ft_conv_args(&list_arg);
			ft_add_cmd(&list_cmd, cmd);
			cmd = ft_new_cmd();
			if (!cmd)
			{
				ft_free_cmds(&list_cmd);
				return (NULL);
			}
			list_arg = NULL;
		}
		if (*token)
			*token = (*token)->next;
	}
	cmd->argv = ft_conv_args(&list_arg);
	ft_add_cmd(&list_cmd, cmd);
	return (list_cmd);
}
