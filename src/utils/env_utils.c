/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 22:06:49 by goramos-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/02/10 12:59:54 by goramos-         ###   ########.fr       */
=======
/*   Updated: 2026/02/04 16:31:25 by goramos-         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
<<<<<<< HEAD
=======

>>>>>>> main

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
	new->value = value ? ft_strdup(value) : NULL;
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
