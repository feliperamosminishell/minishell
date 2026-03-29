/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cnt_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 20:39:55 by juan-her          #+#    #+#             */
/*   Updated: 2026/03/30 00:41:39 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_inst_data(t_cmd **cmd, t_cmd **l_c, t_args **l_ag, t_token **tk)
{
	t_en_token	type;

	type = (*tk)->type;
	if (type == WORD)
		ft_add_args(l_ag, (*tk)->value);
	else if (ft_is_redir(type))
	{
		if (!(*tk)->next || !(*tk)->next->value)
			return (0);
		*tk = (*tk)->next;
		ft_add_redir(&(*cmd)->redirs, type, (*tk)->value, (*tk)->quotes);
	}
	else if (type == PIPE)
	{
		if (!ft_new_pipe(cmd, l_c, l_ag))
			return (0);
	}
	return (1);
}
