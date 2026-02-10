/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:src/lexer/check_str2.c
/*   Created: 2026/02/07 19:03:49 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/10 12:40:15 by goramos-         ###   ########.fr       */
=======
/*   Created: 2025/10/05 04:13:58 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/04 16:20:33 by goramos-         ###   ########.fr       */
>>>>>>> main:libft/ft_lstadd_bonus.c
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

<<<<<<< HEAD:src/lexer/check_str2.c
void	ft_lstadd_token(t_token **lst, t_token *new)
=======
void	ft_lstadd(t_list **lst, t_list *new_node)
>>>>>>> main:libft/ft_lstadd_bonus.c
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
