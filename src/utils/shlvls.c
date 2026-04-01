/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 19:05:57 by goramos-          #+#    #+#             */
/*   Updated: 2026/04/01 21:15:53 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_atoi_shlvl(const char *str)
{
	int	result;

	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 +(*str - '0');
		str++;
	}
	return (result);
}

static void	ft_print_shlvl_warning(void)
{
	ft_putstr_fd("Minishell: warning: shell level(", STDERR_FILENO);
	ft_putstr_fd("1000", STDERR_FILENO);
	ft_putstr_fd(") too high. reseetting to 1\n", STDERR_FILENO);
}

static void	ft_set_shlvl_value(t_env *shlvl_node, int new_value)
{
	char	*new_value_str;

	new_value_str = ft_itoa(new_value);
	if (!new_value_str)
		return ;
	free(shlvl_node->value);
	shlvl_node->value = new_value_str;
}

static int	ft_calculate_new_shlvl(int current_level)
{
	int	new_value;

	if (current_level < 0)
		new_value = 1;
	else
		new_value = current_level + 1;
	if (new_value > 1000)
	{
		ft_print_shlvl_warning();
		new_value = 1;
	}
	return (new_value);
}

void	ft_update_shlvl(t_shell *mini)
{
	t_env	*shlvl_node;
	int		current_value;
	int		new_value;

	shlvl_node = env_find(mini->env, "SHLVL");
	if (!shlvl_node)
	{
		shlvl_node = create_env_node("SHLVL", "1");
		if (shlvl_node)
			add_back_env(&mini->env, shlvl_node);
		return ;
	}
	if (!shlvl_node->value)
	{
		shlvl_node->value = ft_strdup("1");
		return ;
	}
	current_value = ft_atoi_shlvl(shlvl_node->value);
	new_value = ft_calculate_new_shlvl(current_value);
	ft_set_shlvl_value(shlvl_node, new_value);
}
