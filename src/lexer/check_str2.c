/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 04:13:58 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/11 14:21:04 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstadd_token(t_token **lst, t_token *new_node)
{
	t_token	*size;
	
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
