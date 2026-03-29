/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:10:30 by juan-her          #+#    #+#             */
/*   Updated: 2026/03/27 11:21:14 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_free_array(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static char	**ft_search_paths(char **env, int *i)
{
	char	**paths;

	*i = 0;
	while (env[*i] && ft_strnstr(env[*i], "PATH=", 5) == 0)
		(*i)++;
	if (!env[*i])
		return (NULL);
	paths = ft_split(env[*i] + 5, ':');
	*i = -1;
	return (paths);
}

static void	ft_search_path(char *cmd, char **paths, int i, char **path)
{
	char	*url_path;

	url_path = ft_strjoin(paths[i], "/");
	*path = ft_strjoin(url_path, cmd);
	free(url_path);
}

static char	*ft_find_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	int		i;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	paths = ft_search_paths(env, &i);
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		ft_search_path(cmd, paths, i, &path);
		if (access(path, X_OK) == 0)
			return (ft_free_array(paths), path);
		free(path);
	}
	return (ft_free_array(paths), NULL);
}

void	ft_execute(char **cmd, char **env)
{
	char	*path;

	if (!cmd || !*cmd)
		exit(127);
	path = ft_find_path(cmd[0], env);
	if (!path)
	{
		ft_print_error_exec(0, cmd[0]);
		exit(127);
	}
	execve(path, cmd, env);
	if (errno == EISDIR)
		ft_print_error_exec(3, cmd[0]);
	else if (errno == EACCES)
		ft_print_error_exec(1, cmd[0]);
	else
		ft_print_error_exec(2, cmd[0]);
	free(path);
	exit(127);
}
