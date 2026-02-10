/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:03:49 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/10 12:40:15 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstadd_token(t_token **lst, t_token *new)
{
	t_token	*list;

	if (!*lst || !new)
	{
		*lst = new;
		return ;
	}
	list = *lst;
	while (list->next != NULL)
		list = list->next;
	list->next = new;
}
