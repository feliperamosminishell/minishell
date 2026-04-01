/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:14:16 by juan-her          #+#    #+#             */
/*   Updated: 2026/03/31 02:34:52 by juan-her         ###   ########.fr       */
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

static void	ft_exit_shell(t_shell *mini, char *line)
{
	if (line)
		free(line);
	printf("exit\n");
	rl_clear_history();
	exit(mini->exit_status);
}

static int	ft_is_exit_cmd(char *line)
{
	if (!ft_strncmp(line, "exit", 4) && line[4] == '\0')
		return (1);
	return (0);
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
		if (ft_is_exit_cmd(line))
			ft_exit_shell(mini, line);
		if (*line)
		{
			add_history(line);
			ft_handler_line(line, &mini);
		}
		free(line);
	}
}
