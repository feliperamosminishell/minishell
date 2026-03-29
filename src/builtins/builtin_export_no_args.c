/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_no_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 20:22:35 by goramos-          #+#    #+#             */
/*   Updated: 2026/03/27 11:10:17 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_export_no_args(t_shell *shell)
{
	t_env	**env_array;
	int		count;
	int		i;

	count = count_env_vars(shell->env);
	if (count == 0)
		return ;
	env_array = malloc(count * sizeof(t_env *));
	if (!env_array)
	{
		shell->exit_status = 1;
		return ;
	}
	copy_env_to_array(shell->env, env_array);
	sort_env_array(env_array, count);
	i = 0;
	while (i < count)
	{
		print_export_var(env_array[i]);
		i++;
	}
	free(env_array);
}
