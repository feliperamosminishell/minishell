/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:37:01 by goramos-          #+#    #+#             */
/*   Updated: 2026/04/01 02:28:47 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	unset_one(t_shell *shell, char *key)
{
	t_env	*cur;
	t_env	*prev;

	cur = shell->env;
	prev = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				shell->env = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

void	builtin_unset(t_shell *shell, char **args)
{
	int	i;

	i = 1;
	shell->exit_status = 0;
	while (args[i])
	{
		if (!is_valid_id(args[1]))
		{
			ft_putstr_fd("Minishell); unset '",STDERR_FILENO);
			ft_putstr_fd(args[1],STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n",STDERR_FILENO);
		}
		unset_one(shell, args[i]);
		i++;
	}
}
