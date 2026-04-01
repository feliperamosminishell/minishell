/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 01:53:29 by juan-her          #+#    #+#             */
/*   Updated: 2026/04/01 01:50:07 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_get_env_value(t_env *env, char *var)
{
	t_env	*node;

	node = env_find(env, var);
	if (!node || !node -> value)
		return (ft_strdup(""));
	return (ft_strdup(node->value));
}

char	*ft_expand_var(const char *line, int *i, int last_status, t_env *env)
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
	if (*i == start)
		return (ft_strdup("$"));
	var = ft_substr(line, start, *i - start);
	value = ft_get_env_value(env, var);
	free(var);
	if (!value)
		return (ft_strdup(""));
	return (value);
}

void	ft_write_pipe(char *line, int last_status, int fd, t_env *env)
{
	char	*str;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			str = ft_expand_var(line, &i, last_status, env);
			write(fd, str, ft_strlen(str));
			free(str);
		}
		else
		{
			write(fd, &line[i], 1);
			i++;
		}
	}
}
