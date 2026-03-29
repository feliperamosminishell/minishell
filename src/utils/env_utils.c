/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 22:06:49 by goramos-          #+#    #+#             */
/*   Updated: 2026/03/29 22:46:00 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_back_env(t_env **list, t_env *new_node)
{
	t_env	*last;

	if (!list || !new_node)
		return ;
	if (!*list)
	{
		*list = new_node;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new_node;
}

static t_env	*create_env_node_from_str(char *env_str)
{
	t_env	*new;
	char	*sep;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	sep = ft_strchr(env_str, '=');
	if (sep)
	{
		new->key = ft_substr(env_str, 0, sep - env_str);
		new->value = ft_strdup(sep + 1);
	}
	else
	{
		new->key = ft_strdup(env_str);
		new->value = NULL;
	}
	new->next = NULL;
	return (new);
}

t_env	*create_env_node(const char *key, const char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = NULL;
	if (value)
		new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

t_env	*init_env(char **envp)
{
	t_env	*env_list;
	t_env	*new_node;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp && envp[i])
	{
		new_node = create_env_node_from_str(envp[i]);
		if (new_node)
			add_back_env(&env_list, new_node);
		i++;
	}
	return (env_list);
}

t_env	*env_find(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
