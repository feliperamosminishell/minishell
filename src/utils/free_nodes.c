/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:57:55 by juan-her          #+#    #+#             */
/*   Updated: 2026/04/01 00:51:21 by goramos-         ###   ########.fr       */
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

	if (!ags || !*ags)
		return ;
	while (*ags)
	{
		ag = (*ags)->next;
		if ((*ags)->ag)
			free ((*ags)->ag);
		free (*ags);
		*ags = ag;
	}
}

void	ft_free_redirs(t_redir **redir)
{
	t_redir	*tmp;

	if (!redir || !*redir)
		return ;
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

	if (!cmd || !*cmd)
		return ;
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
		if ((*cmd)->redirs)
			ft_free_redirs(&(*cmd)->redirs);
		free(*cmd);
		*cmd = tmp;
	}
}
