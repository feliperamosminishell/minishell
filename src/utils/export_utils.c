/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 20:24:57 by goramos-          #+#    #+#             */
/*   Updated: 2026/03/18 00:37:52 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

/*funcion para contar variables de entorno de shell->env_list*/
int count_env_vars(t_env *env)
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
void copy_env_to_array(t_env *env, t_env **array)
{
	int		i;
	t_env	*current;

	i = 0;
	current = env;
	while (current)
	{
		array[i] = current;
		current =  current->next;
		i++;
	}	
}
/*bubblesort de ese array de variables*/
void sort_env_array(t_env **array, int count)
{
	int		i;
	int		j;
	t_env	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(array[j]->key, array[j + 1]->key) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static void print_escaped_value(const char *value)
{
	int i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '"' || value[i] == '\\')
			write(1, "\\", 1);
		write(1, &value[i], 1);
		i++;
	}
}

void print_export_var(t_env *env)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(env->key, 1);
	if (env->value != NULL)
	{
		ft_putstr_fd("=\"", 1);
		print_escaped_value(env->value);
		ft_putstr_fd("\"", 1);
	}
	ft_putstr_fd("\n", 1);
}

char	*get_key(char *arg)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
		return (ft_substr(arg, 0, eq - arg));
	return (ft_strdup(arg));
}
char	*get_value(char *arg)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
		return (ft_strdup(eq + 1));
	return (NULL);
}

int	is_valid_id(char *key)
{
	int	i;

	if (!key || (!ft_isalpha((unsigned char)key[0]) && key[0] != '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum((unsigned char)key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}