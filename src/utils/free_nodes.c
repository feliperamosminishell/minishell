/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:57:55 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/18 16:32:25 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_tokens(t_token **token)
{
	t_token	*tok;

	while (*token)
	{
		tok = (*token)->next;
		free((*token)->value);
		free(*token);
		*token = tok;
	}
}

void	ft_free_args(t_args **ags)
{
	t_args	*ag;

	while (*ags)
	{
		ag = (*ags)->next;
		free ((*ags)->ag);
		free (*ags);
		*ags = ag;
	}
}

void	ft_free_redirs(t_redir **redir)
{
	t_redir	*tmp;

	while (*redir)
	{
		tmp = (*redir)->next;
		if ((*redir)->file)
			free((*redir)->file);
		free(*redir);
		*redir = tmp;
	}
}

void	ft_free_cmds(t_cmd **cmd)
{
	int		i;
	t_cmd	*tmp;

	while (*cmd)
	{
		tmp = (*cmd)->next;
		if ((*cmd)->argv)
		{
			i = 0;
			while ((*cmd)->argv[i])
				free((*cmd)->argv[i++]);
			free((*cmd)->argv);
		}
		ft_free_redirs(&(*cmd)->redirs);
		free(*cmd);
		*cmd = tmp;
	}
}
