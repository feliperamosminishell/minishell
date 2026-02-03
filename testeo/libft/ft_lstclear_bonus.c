/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 04:41:01 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/03 22:32:23 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear(t_token **lst)
{
	t_token	*list;
	t_token	*tmp;

	if (!*lst)
		return ;
	list = *lst;
	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
	*lst = NULL;
}
