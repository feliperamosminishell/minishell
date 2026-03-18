/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 19:23:22 by goramos-          #+#    #+#             */
/*   Updated: 2026/03/18 00:22:29 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_env_list(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (current->value != NULL)
		{
			ft_putstr_fd(current->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(current->value, 1);
			ft_putstr_fd("\n", 1);
		}
		current = current->next;
	}
}

int	builtin_env(char **argv, t_shell *shell)
{
	if (argv && argv[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		shell->exit_status = 1;
		return (1);
	}
	if (!shell->env_bash)
		return (0);
	print_env_list(shell->env);
	return (0);
}