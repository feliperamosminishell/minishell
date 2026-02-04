/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 03:02:24 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/04 01:23:06 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*size;

	i = 0;
	size = lst;
	while (size)
	{
		i++;
		size = size->next;
	}
	return (i);
}
