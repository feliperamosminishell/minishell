/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 05:05:51 by juan-her          #+#    #+#             */
/*   Updated: 2026/01/31 16:17:53 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_token *lst, void (*f)(int))
{
	t_token	*list;

	if (!lst || !f)
		return ;
	list = lst;
	while (list)
	{
		f(list->type);
		list = list->next;
	}
}
