/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:47:46 by goramos-          #+#    #+#             */
/*   Updated: 2026/04/16 16:56:09 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstadd_token(t_token **lst, t_token *new_node)
{
	t_token	*tmp;

	if (!*lst || !new_node)
	{
		*lst = new_node;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_node;
}

void	ft_print_message(int fd, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		write(fd, &str[i++], 1);
}

void	close_pipe(int prev_pipe)
{
	if (prev_pipe != -1)
		close(prev_pipe);
}

int	is_limiter(char *line, char *limiter)
{
	if (!line || !limiter)
		return (0);
	return (ft_strlen(line) == ft_strlen(limiter)
		&& ft_strncmp(line, limiter, ft_strlen(limiter)+1) == 0);
}
