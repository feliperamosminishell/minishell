/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_no_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 20:22:35 by goramos-          #+#    #+#             */
/*   Updated: 2026/02/18 16:28:37 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_export(t_shell *shell, char **args)
{
	t_env	**env_array;
	int		count;
	int		i;

	if (args[1] != NULL)
	{
		ft_putstr_fd("minishell: export: too many arguments\n", 2);
		shell->exit_status = 1;
		return (0);
	}
	count = count_env_vars(shell->env);
	env_array = malloc(count * sizeof(t_env *));
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
