/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 04:13:58 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/04 16:20:33 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **lst, t_list *new_node)
{
	t_list	*size;

	if (!*lst || !new_node)
	{
		*lst = new_node;
		return ;
	}
	size = *lst;
	while (size->next != NULL)
		size = size->next;
	size->next = new_node;
}
