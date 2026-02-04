/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 02:03:23 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/04 01:49:09 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"
/*
t_token	*ft_new_token(int type, char *value)
{
	t_token	*list;
	(void)value;

	list = malloc(sizeof(t_shell));
	if (!list)
		return (NULL);
	list->type = type;
	list->next = NULL;
	return (list);
}

*/
t_list	*ft_lstnew(void *content,char *value)
{
	t_list	*list;
	(void)value;

	list = (t_list *) malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}
