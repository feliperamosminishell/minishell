/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 20:24:57 by goramos-          #+#    #+#             */
/*   Updated: 2026/02/18 16:31:49 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*funcion para contar variables de entorno de shell->env_list*/
int	count_env_vars(t_env *env)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/*copiar estas variables a un array*/
void	copy_env_to_array(t_env *env, t_env **array)
{
	int		i;
	t_env	*current;

	i = 0;
	current = env;
	while (current)
	{
		array[i] = current;
		current = current->next;
		i++;
	}
}
/*bubblesort de ese array de variables*/
