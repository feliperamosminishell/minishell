/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 03:03:59 by juan-her          #+#    #+#             */
/*   Updated: 2026/03/31 02:52:59 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_check_inst(t_token **tk, t_cmd **l_c, t_cmd **cmd, t_args **l_a)
{
	if (!ft_inst_data(cmd, l_c, l_a, tk))
	{
		ft_free_cmds(l_c);
		ft_free_args(l_a);
		if (*cmd)
		{
			ft_free_redirs(&(*cmd)->redirs);
			free(*cmd);
		}
		return (0);
	}
	*tk = (*tk)->next;
	return (1);
}

static t_cmd	*ft_separate_token(t_token **token)
{
	t_args	*list_arg;
	t_cmd	*list_cmd;
	t_cmd	*cmd;

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
		if (!ft_check_inst(token, &list_cmd, &cmd, &list_arg))
			return (NULL);
	}
	if (list_arg)
		cmd->argv = ft_conv_args(&list_arg);
	if (cmd->redirs || cmd->argv)
		ft_add_cmd(&list_cmd, cmd);
	else
		ft_free_cmds(&cmd);
	return (list_cmd);
}

t_cmd	*ft_parser(t_token **token, t_shell **mini)
{
	t_cmd	*cmd;

	cmd = ft_separate_token(token);
	if (!cmd)
		return (NULL);
	if (!ft_check_files(cmd->redirs))
	{
		(*mini)->exit_status = 130;
		ft_free_cmds(&cmd);
		return (NULL);
	}
	return (cmd);
}
