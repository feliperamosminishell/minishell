/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 05:05:51 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/03 22:32:32 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
