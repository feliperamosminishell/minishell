/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 15:53:13 by juan-her          #+#    #+#             */
/*   Updated: 2026/03/27 11:12:44 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_builtin(char *cmd)
{
	const char	*cte_cmd;

	if (!cmd)
		return (0);
	cte_cmd = (const char *) cmd;
	if (ft_strcmp(cte_cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cte_cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cte_cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cte_cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cte_cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cte_cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cte_cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cte_cmd, "unset") == 0)
		return (1);
	return (0);
}

void	ft_exc_built(t_shell **mini, t_cmd *cmd)
{
	char		**args;
	const char	*cte_cmd;

	cte_cmd = (const char *)cmd->argv[0];
	args = cmd->argv;
	if (ft_strcmp(cte_cmd, "cd") == 0)
		(*mini)->exit_status = builtin_cd(*mini, args);
	else if (ft_strcmp(cte_cmd, "echo") == 0)
		(*mini)->exit_status = builtin_echo(args);
	else if (ft_strcmp(cte_cmd, "env") == 0)
		(*mini)->exit_status = builtin_env(args, *mini);
	else if (ft_strcmp(cte_cmd, "export") == 0)
	{
		if (!args[1])
			builtin_export_no_args(*mini);
		else
			builtin_export_with_args(*mini, args);
	}
	else if (ft_strcmp(cte_cmd, "exit") == 0)
		builtin_exit(*mini, args);
	else if (ft_strcmp(cte_cmd, "pwd") == 0)
		(*mini)->exit_status = builtin_pwd(*mini);
	else if (ft_strcmp(cte_cmd, "unset") == 0)
		builtin_unset(*mini, args);
}
