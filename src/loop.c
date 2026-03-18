/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:14:16 by juan-her          #+#    #+#             */
/*   Updated: 2026/03/18 16:52:49 by juan-her         ###   ########.fr       */
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
	{
		ft_exec(mini);
		ft_free_cmds(&(*mini)->cmds);
	}
}



void ft_loop(t_shell *mini)
{
	char *line;

	while (1)
	{
		WHO_SIG = 0;
		line = readline("Minishell> ");
		if (!line)
		{
			printf("exit\n");
			rl_clear_history();
			exit(mini->exit_status);
		}
		if (WHO_SIG)
		{
			mini->exit_status = 130;
			WHO_SIG = 0;
		}
		if (!ft_strncmp(line, "exit", 4) && line[4] == '\0')
		{
			free(line);
			printf("exit\n");
			rl_clear_history();
			exit(mini->exit_status);
		}
		if (*line)
		{
			add_history(line);
			ft_handler_line(line, &mini);
		}
		free(line);
	}
}
