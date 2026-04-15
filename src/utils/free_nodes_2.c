/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nodes_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 23:24:25 by goramos-          #+#    #+#             */
/*   Updated: 2026/04/15 07:03:54 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_env_node(t_env *node)
{
	if (!node)
		return ;
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

void	ft_free_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env->next;
		ft_free_env_node(env);
		env = tmp;
	}
}

void	ft_free_shell(t_shell *mini)
{
	if (!mini)
		return ;
	if (mini->cmds)
	{
		ft_free_cmds(&mini->cmds);
		mini->cmds = NULL;
	}
	if (mini->env)
	{
		ft_free_env(mini->env);
		mini->env = NULL;
	}
	if (mini->pwd_data.pwd)
	{
		free(mini->pwd_data.pwd);
		mini->pwd_data.pwd = NULL;
	}
	if (mini->pwd_data.old_pwd)
	{
		free(mini->pwd_data.old_pwd);
		mini->pwd_data.old_pwd = NULL;
	}
}

void	ft_close_fds(t_shell *shell)
{
	dup2(shell->stdin_backup, STDIN_FILENO);
	dup2(shell->stdout_backup, STDOUT_FILENO);
	close(shell->stdin_backup);
	close(shell->stdout_backup);
}
