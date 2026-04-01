/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 20:45:28 by goramos-          #+#    #+#             */
/*   Updated: 2026/03/30 19:38:26 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cd_update_env(t_shell *shell, const char *old, const char *new)
{
	t_env	*node;

	node = env_find(shell->env, "OLDPWD");
	if (node)
		env_update(node, old);
	else
		add_back_env(&shell->env, create_env_node("OLDPWD", old));
	node = env_find(shell->env, "PWD");
	if (node)
		env_update(node, new);
	else
		add_back_env(&shell->env, create_env_node("PWD", new));
	free(shell->pwd_data.old_pwd);
	shell->pwd_data.old_pwd = ft_strdup(old);
	free(shell->pwd_data.pwd);
	shell->pwd_data.pwd = ft_strdup(new);
}

static int	cd_error(t_shell *shell, const char *msg, const char *arg)
{
	char	*m;
	char	*ar;

	m = (char *)msg;
	ar = (char *)arg;
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(ar, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(m, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	shell->exit_status = 1;
	return (1);
}

static int	cd_do(t_shell *shell, const char *path)
{
	char	old[4096];
	char	new[4096];

	if (chdir(path) != 0)
		return (cd_error(shell, strerror(errno), path));
	if (!getcwd(new, sizeof(new)))
		return (cd_error(shell, "getcwd failed", NULL));
	cd_update_env(shell, old, new);
	shell->exit_status = 0;
	return (0);
}

static int	cd_dash(t_shell *shell)
{
	t_env	*node;

	node = env_find(shell->env, "OLDPWD");
	if (!node || !node->value)
		return (cd_error(shell, "OLDPWD not set", NULL));
	ft_putstr_fd(node->value, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (cd_do(shell, node->value));
}

int	builtin_cd(t_shell *shell, char **argv)
{
	t_env	*home;

	if (argv[1] && argv[2])
		return (cd_error(shell, "too many arguments", NULL));
	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
	{
		home = env_find(shell->env, "HOME");
		if (!home || !home->value)
			return (cd_error(shell, "HOME not set", NULL));
		return (cd_do(shell, home->value));
	}
	if (ft_strcmp(argv[1], "-") == 0)
		return (cd_dash(shell));
	return (cd_do(shell, argv[1]));
}
