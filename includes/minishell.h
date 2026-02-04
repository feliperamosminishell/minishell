/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:48:48 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/04 01:42:44 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#  define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
# include "../libft/libft.h"

typedef enum e_token
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	DOUBLEQ,
	SINGLEQ
} t_token_type;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;
} t_token;

typedef struct s_redir
{
	char	*file;
	t_token_type type;
	struct s_redir *next; // Añadido: para tener múltiples redirecciones (ej: > file1 > file2)
} t_redir;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
} t_env;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
} t_cmd;

typedef struct s_shell
{
	t_env	*env;
	t_cmd	*cmds;
	char	*pwd;
	char	*oldpwd;
	int		cmd_count;
	int		exit_status;
} t_shell;


// ========== FUNCTION PROTOTYPES ==========

// Loop
void    ft_loop(t_shell *mini);

// Parsing
int     ft_check_str(char *str);
t_token *ft_lexer(const char *line);
char    *expand_var(const char *line, int *i);

// Utils
void    ft_freelist(t_list **list);

// Environment
t_env   *init_env(char **envp);
void    add_back_env(t_env **list, t_env *new_node);
void    free_env(t_env *env);

#endif
