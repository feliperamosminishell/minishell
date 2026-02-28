/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:14:16 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/28 22:38:27 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_handler_line(char *line, t_shell **mini)
{
	t_token	*tokens;
	t_token	*head;

	head = ft_lexer(line, 1);
	tokens = head;
	(*mini)->cmds = ft_parser(&tokens);
	ft_free_tokens(&head);
	if ((*mini)->cmds)
	{
		ft_exec(mini);
		ft_free_cmds(&(*mini)->cmds);
	}
	free(line);
}

void	ft_loop(t_shell *mini)
{
	char	*line;

	while (1)
	{
		mini->cmds = NULL;
		line = readline("Minishell> ");
		if (!ft_strncmp(line, "exit", 5))
		{
			free(line);
			break ;
		}
		if (*line)
		{
			add_history(line);
			ft_handler_line(line, &mini);
		}
	}
}
