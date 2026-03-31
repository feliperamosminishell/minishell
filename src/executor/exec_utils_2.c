/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 00:47:51 by goramos-          #+#    #+#             */
/*   Updated: 2026/04/01 00:48:21 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_check_paths(char *cmd, char **paths, int i)
{
	char	*path;

	while (paths[++i])
	{
		ft_search_path(cmd, paths, i, &path);
		if (access(path, X_OK) == 0)
		{
			ft_free_array(paths);
			return (path);
		}
		free(path);
	}
	ft_free_array(paths);
	return (NULL);
}
