/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:56:37 by juan-her          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/02/08 05:07:20 by juan-her         ###   ########.fr       */
=======
/*   Updated: 2026/02/04 15:51:19 by goramos-         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <stddef.h>
# include <limits.h>
<<<<<<< HEAD
=======

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
/*
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
} t_redir;

typedef struct s_cmd
{
	char    **argv;
	t_redir *redirs;
	int     fd_in;
	int     fd_out;
} t_cmd;
*/

/*Edicion añadir pwd para builtin cd y pwd*/
/*
typedef struct s_shell
{
	char	pwd[PATH_MAX];
	t_cmd   *cmds;
	int     cmd_count;
	char    **env;
	int     exit_status;
} t_shell;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
} t_env;
*/

>>>>>>> main

size_t	ft_strlen(const char *s);
long	ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
<<<<<<< HEAD
=======
int		ft_lstsize(t_list *lst);
/*
t_token	*ft_new_token(int type, char *value);
*/
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_freelist(t_list **list);
>>>>>>> main
int		ft_isspace (char c);
void	ft_multifree(int n, ...);

#endif
