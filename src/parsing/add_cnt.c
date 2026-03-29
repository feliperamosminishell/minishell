/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cnt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 02:55:14 by juan-her          #+#    #+#             */
/*   Updated: 2026/03/30 00:41:39 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_add_args(t_args **list, char *value)
{
	t_args	*new;
	t_args	*tmp;

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

int	ft_add_redir(t_redir **list, t_en_token type, char *file, int quotes)
{
	t_redir	*new;
	t_redir	*tmp;

	new = ft_new_redir(ft_strdup(file), type, quotes);
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

char	**ft_conv_args(t_args **ag)
{
	int		count[2];
	char	**args;
	t_args	*next;
	t_args	*tmp;

	count[0] = 0;
	count[1] = 0;
	tmp = *ag;
	while (tmp)
	{
		count[1]++;
		tmp = tmp->next;
	}
	args = ft_calloc((count[1] + 1), sizeof(char *));
	if (!args)
		return (NULL);
	tmp = *ag;
	while (tmp)
	{
		args[count[0]++] = tmp->ag;
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	return (*ag = NULL, args);
}

void	ft_add_cmd(t_cmd **list, t_cmd *new)
{
	t_cmd	*tmp;

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

int	ft_new_pipe(t_cmd **cmd, t_cmd **l_c, t_args **list_ag)
{
	(*cmd)->argv = ft_conv_args(list_ag);
	ft_add_cmd(l_c, *cmd);
	*cmd = ft_new_cmd();
	if (!*cmd)
		return (ft_free_cmds(l_c), 0);
	*list_ag = NULL;
	return (1);
}
