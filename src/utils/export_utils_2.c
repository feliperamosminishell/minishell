/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 11:52:31 by goramos-          #+#    #+#             */
/*   Updated: 2026/03/27 11:56:48 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_escaped_value(const char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '"' || value[i] == '\\')
			write(1, "\\", 1);
		write(1, &value[i], 1);
		i++;
	}
}

void	print_export_var(t_env *env)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(env->key, 1);
	if (env->value != NULL)
	{
		ft_putstr_fd("=\"", 1);
		print_escaped_value(env->value);
		ft_putstr_fd("\"", 1);
	}
	ft_putstr_fd("\n", 1);
}

char	*get_key(char *arg)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
		return (ft_substr(arg, 0, eq - arg));
	return (ft_strdup(arg));
}

char	*get_value(char *arg)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
		return (ft_strdup(eq + 1));
	return (NULL);
}

int	is_valid_id(char *key)
{
	int	i;

	if (!key || (!ft_isalpha((unsigned char)key[0]) && key[0] != '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum((unsigned char)key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
