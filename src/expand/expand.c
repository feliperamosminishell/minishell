/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 01:53:29 by juan-her          #+#    #+#             */
/*   Updated: 2026/03/16 19:43:08 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_expand_var(const char *line, int *i, int last_status)
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

void	ft_write_pipe(char *line, int last_status, int fd)
{
	char *str;
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			str = ft_expand_var(line, &i, last_status);
			write(fd, str, ft_strlen(str));
		}
		else
		{
			write(fd, &line[i], 1);
			i++;
		}
	}
}
