/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 01:53:29 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/10 12:38:03 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *ft_expand_var(const char *line, int *i, int last_status)
{
	int		start;
	char	*var;
	char	*value;

	(*i)++;
	if (line[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(last_status));
	}
	start = *i;
	while (ft_isalnum(line[*i]) || line[*i] == '_')
		(*i)++;
	var = ft_substr(line, start, *i - start);
	value = getenv(var);
	free(var);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}
