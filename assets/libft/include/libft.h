/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 17:12:49 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/11 18:45:10 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdarg.h>
# include <fcntl.h>

typedef struct s_list
{
	void			*key;
	void			*value;
	struct s_list	*next;
}					t_list;

typedef struct s_token
{
	int				key;
	char			*value;
	int				len;
	struct s_token	*next;
}					t_token;

void		ft_bzero(void *s, size_t n);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
void		*ft_memcpy(void *dest, const void *src, size_t len);
void		*ft_memmove(void *dest, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dest, const char *src, size_t len);
size_t		ft_strlcat(char *dest, const char *src, size_t len);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_atoi(const char *str);
char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_itoalong(long n);
// for built-ins
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
size_t		ft_putstr(char *str);
size_t		ft_putchar(int c);
size_t		ft_putdec(int n);
size_t		ft_putdeclong(unsigned int n);
int			ft_putvoid(void *p);
int			ft_puthexa(unsigned long long nb, char ch);
//
double		ft_atof(char *str);
int			ft_isspace(int c);
void		*ft_calloc(size_t count, size_t size);
t_list		*ft_lstnew(void *key, void *value);
void		ft_lstadd_back(t_list **lst, t_list *new);
t_list		*ft_lstlast(t_list *lst);
char		*ft_strndup(const char *s, size_t n);
int			ft_is_special_char(char c);
void		ft_lstadd_front(t_list **lst, t_list *new);
// Token type func
t_token		*ft_tokennew(int key, char *value);
void		ft_tokadd_back(t_token **lst, t_token *new);
void		ft_tokadd_front(t_token **lst, t_token *new);
//
#endif
