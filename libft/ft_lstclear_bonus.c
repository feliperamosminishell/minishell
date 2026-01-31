/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 04:41:01 by juan-her          #+#    #+#             */
/*   Updated: 2026/01/31 16:17:38 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
