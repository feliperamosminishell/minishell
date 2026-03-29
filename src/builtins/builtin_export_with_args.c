/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_with_args.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:58:03 by goramos-          #+#    #+#             */
/*   Updated: 2026/03/27 11:18:51 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	export_check_key(t_shell *shell, char *key, char *arg)
{
	if (is_valid_id(key))
		return (1);
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	free(key);
	shell->exit_status = 1;
	return (0);
}

static void	export_one_arg(t_shell *shell, char *arg)
{
	char	*key;
	char	*val;
	t_env	*node;
	int		has_value;

	key = get_key(arg);
	if (!export_check_key(shell, key, arg))
		return ;
	has_value = (ft_strchr(arg, '=') != NULL);
	val = get_value(arg);
	node = env_find(shell->env, key);
	if (node)
	{
		if (has_value)
			env_update(node, val);
	}
	else
		add_back_env(&shell->env, create_env_node(key, val));
	free(key);
	free(val);
}

void	builtin_export_with_args(t_shell *shell, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		export_one_arg(shell, args[i]);
		i++;
	}
}
