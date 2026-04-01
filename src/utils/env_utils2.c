/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 22:43:33 by goramos-          #+#    #+#             */
/*   Updated: 2026/04/01 21:17:52 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_update(t_env *node, const char *new_value)
{
	if (!node)
		return ;
	free(node->value);
	if (new_value)
		node->value = ft_strdup(new_value);
	else
		node->value = NULL;
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

static char	*ft_env_entry(t_env *node)
{
	char	*joined;
	char	*result;

	joined = ft_strjoin(node->key, "=");
	if (node->value)
		result = ft_strjoin(joined, node->value);
	else
		result = ft_strjoin(joined, "");
	free(joined);
	return (result);
}

char	**ft_env_to_array(t_env *env)
{
	t_env	*tmp;
	char	**arr;
	int		i;
	int		count;

	count = 0;
	tmp = env;
	while (tmp && ++count)
		tmp = tmp->next;
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		arr[i] = ft_env_entry(tmp);
		tmp = tmp->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
