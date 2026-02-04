/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:48:48 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/04 16:30:42 by goramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
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
	char			*file;
	t_token_type	type;
	struct s_redir	*next;
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
	t_env	*env_list;
	t_cmd	*cmds;
	char	*pwd;
	char	*oldpwd;
	int		cmd_count;
	int		exit_status;
} t_shell;


// ========== FUNCTION PROTOTYPES ==========

// Loop
void	ft_loop(t_shell *mini);

// Parsing
int		ft_check_str(char *str);
t_token	*ft_lexer(const char *line);
char	*expand_var(const char *line, int *i);

// Utils
void	ft_freelist(t_list **list);

// Environment
t_env	*init_env(char **envp);
void	add_back_env(t_env **list, t_env *new_node);
void	free_env(t_env *env);

// ========== BUILTINS ==========
int		is_builtin(char *cmd);
void	execute_builtin(t_shell *shell, t_cmd *cmd);

// Builtins individuales
int		builtin_echo(char **args);
void	builtin_cd(t_shell *shell, char **args);
int		builtin_pwd(t_shell *sh);
void	builtin_export(t_shell *shell, char **args);
void	builtin_unset(t_shell *shell, char **args);
int		builtin_env(char **argv, t_shell *shell);
void	builtin_exit(t_shell *shell, char **args);
void	print_env_list(t_env *env_list);

// ========== ENV UTILS ==========
char	*get_env_value(t_env *env, const char *key);
void	set_env_value(t_env **env, const char *key, const char *value);
void	unset_env_value(t_env **env, const char *key);
t_env	*create_env_node(const char *key, const char *value);

// ========== EXECUTOR ==========
void	execute_command(t_shell *shell, t_cmd *cmd);

// ========== UTILS ==========
t_token	*ft_new_token(int type, char *value);
void	ft_token_add_back(t_token **list, t_token *new);



#endif
