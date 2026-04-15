/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:14:16 by juan-her          #+#    #+#             */
/*   Updated: 2026/04/15 06:43:49 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_handler_line(char *line, t_shell **mini)
{
	t_token	*tokens;
	t_token	*head;

	head = ft_lexer(line, (*mini)->exit_status, mini);
	tokens = head;
	(*mini)->cmds = ft_parser(&tokens, mini);
	ft_free_tokens(&head);
	if ((*mini)->cmds)
		ft_exec(mini);
	if ((*mini)->cmds)
	{
		ft_free_cmds(&(*mini)->cmds);
		(*mini)->cmds = NULL;
	}
}

static void	ft_exit_shell(t_shell *mini, char *line)
{
	int	status;

	status = mini->exit_status;
	if (line)
		free(line);
	printf("exit\n");
	ft_free_shell(mini);
	rl_clear_history();
	exit(status);
}

void	ft_loop(t_shell *mini)
{
	char	*line;

	while (1)
	{
		g_who_sig = 0;
		line = readline("Minishell> ");
		if (!line)
			ft_exit_shell(mini, NULL);
		if (g_who_sig)
			g_who_sig = 0;
		if (*line)
		{
			add_history(line);
			ft_handler_line(line, &mini);
		}
		free(line);
	}
}
