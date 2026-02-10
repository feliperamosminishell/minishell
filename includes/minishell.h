/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:48:48 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/10 12:36:25 by goramos-         ###   ########.fr       */
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
} en_token;

typedef struct s_token
{
	char            *value;
	en_token         type;
	struct s_token  *next;
} t_token;

typedef struct s_redir
{
	char    *file;
	en_token type;
	struct s_redir	*next;
} t_redir;

typedef struct s_args
{
	char	*ag;
	struct s_args *next;
} t_args;

typedef struct s_cmd
{
	char    **argv;
	t_redir *redirs;
	int     fd_in;
	int     fd_out;
	struct s_cmd *next;
} t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
} t_env;

typedef struct s_pwd
{
	char	*pwd;
	char	*old_pwd;
} t_pwd;

typedef struct s_shell
{
	t_cmd   *cmds;
	char    **env_bash;
	t_env	*env;
	t_pwd	pwd_data;
	int     exit_status;
} t_shell;


// ========== FUNCTION PROTOTYPES ==========

// ==========  LOOP ==========
void	ft_loop(t_shell *mini);

// ==========  UTILS ==========
t_token	*ft_new_token(int type, char *value);
t_args	*ft_new_args(char *str);
t_cmd	*ft_new_cmd(void);
t_redir	*ft_new_redir(char *file, en_token type);
void	ft_free_tokens(t_token **token);
void	ft_free_args(t_args **ags);
void	ft_free_redirs(t_redir **redir);
void 	ft_free_cmds(t_cmd **cmd);
t_env	*init_env(char **envp);
void	add_back_env(t_env **list, t_env *new_node);
void	free_env(t_env *env);

// ==========  CHECK LINE ==========
int	ft_check_str(const char *str);

// ==========  LEXER ==========
void	ft_lstadd_token(t_token **lst, t_token *new);
t_token *ft_lexer(const char *line, int last_status);

// ==========  PARSING ==========
int		ft_add_args(t_args **list, char *value);
int		ft_add_redir (t_redir **list, en_token type, char *file);
char	**ft_conv_args(t_args **ag);
void	ft_add_cmd(t_cmd **list, t_cmd *new);
t_cmd	*ft_parser(t_token **token);

// ========== BUILTINS ==========
int		is_builtin(char *cmd);
void	execute_builtin(t_shell *shell, t_cmd *cmd);

// ========== INDIVIDUAL BUILTINS ==========
int		builtin_echo(char **args);
//void	builtin_cd(t_shell *shell, char **args);
int		builtin_pwd(t_shell *sh);
//void	builtin_export(t_shell *shell, char **args);
//void	builtin_unset(t_shell *shell, char **args);
int		builtin_env(char **argv, t_shell *shell);
//void	builtin_exit(t_shell *shell, char **args);
void	print_env_list(t_env *env_list);

// ========== EXPAND ==========
char	*ft_expand_var(const char *line, int *i, int last_status);


// ========== EXECUTOR ==========
//void	execute_command(t_shell *shell, t_cmd *cmd);


#endif
