/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 22:43:33 by goramos-          #+#    #+#             */
/*   Updated: 2026/04/01 01:41:51 by goramos-         ###   ########.fr       */
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

void	ft_free_env(t_env *env)
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

char	**ft_env_to_array(t_env *env)
{
	t_env	*tmp;
	char	**arr;
	char	*joined;
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
		joined = ft_strjoin(tmp->key, "=");
		arr[i] = ft_strjoin(joined, tmp->value ? tmp->value : "");
		free(joined);
		tmp = tmp->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
