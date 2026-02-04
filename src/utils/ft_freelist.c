/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freelist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:42:34 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/04 01:26:32 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freelist(t_list **list)
{
	t_token	*temp;

	while (*list)
	{
		temp = (*list)->next;
		free(*list);
		*list = temp;
	}
}
