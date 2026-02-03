/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 03:02:24 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/03 22:32:44 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize(t_token *lst)
{
	int		i;
	t_token	*size;

	i = 0;
	size = lst;
	while (size)
	{
		i++;
		size = size->next;
	}
	return (i);
}
