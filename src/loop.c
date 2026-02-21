/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:14:16 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/19 13:35:19 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_see(t_cmd *parser)
{
	int		i;
	t_cmd	*tmp;
	t_redir	*tmp_r;

	tmp = parser;
	while (tmp)
	{
		i = 0;
		tmp_r = tmp->redirs;
		while (tmp->argv[i])
		{
			while (tmp_r)
			{
				printf("%s redirecciones\n", tmp_r->file);
				printf("%d tipo\n", tmp_r->type);
				tmp_r = tmp_r->next;
			}
			printf("%s comando\n", tmp->argv[i]);
			i++;
		}
		if (tmp->next)
			printf("Otro comando \n");
		tmp = tmp->next;
	}
}

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
		ft_see((*mini)->cmds);
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
