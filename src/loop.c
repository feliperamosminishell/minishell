/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:14:16 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/10 13:02:54 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void ft_see(t_cmd *parser)
{
	int	i;

	while (parser)
	{
		i = 0;
		while (parser->argv[i])
			printf("%s \n", parser->argv[i++]);
		printf("Otro comando \n");
		parser = parser->next;
	}
}

void ft_loop(t_shell *mini)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmds;

	(void)mini;
	while (1)
	{
		line = readline("minishel> ");
		if (!ft_strncmp(line, "exit", 5))
			break ;
		if (*line)
		{
			tokens = ft_lexer(line, 1);
			cmds = ft_parser(&tokens);
			ft_see(cmds);
			add_history(line);
		}
	}
}
