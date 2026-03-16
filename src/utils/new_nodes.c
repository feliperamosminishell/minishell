/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:14:01 by juan-her          #+#    #+#             */
/*   Updated: 2026/03/16 14:52:22 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_new_token(int type, char *value, int quotes)
{
	t_token	*list;

	list = malloc(sizeof(t_token));
	if (!list)
		return (NULL);
	list->value = value;
	list->type = type;
	list->quotes = quotes;
	list->next = NULL;
	return (list);
}

t_args	*ft_new_args(char *str)
{
	t_args	*ag;

	ag = (t_args *) ft_calloc(1, sizeof(t_args));
	if (!ag)
		return (NULL);
	ag->ag = str;
	ag->next = NULL;
	return (ag);
}

t_cmd	*ft_new_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_redir	*ft_new_redir(char *file, en_token type, int quotes)
{
	t_redir	*redir;

	redir = (t_redir *) ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = file;
	redir->type = type;
	redir->quotes = quotes;
	redir->next = NULL;
	return (redir);
}
