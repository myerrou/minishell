/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:47:01 by bjniane           #+#    #+#             */
/*   Updated: 2024/11/24 08:19:26 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define SIZE_MAX LONG_MAX

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				*ft_malloc(size_t size);
void				free_trash(void);
void				ft_lstclear(t_list **lst, void (*del)(void *));

int					ft_isprint(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isdigit(int c);
int					ft_isascii(int c);
int					ft_atoi(const char *str);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_toupper(int c);
int					ft_tolower(int c);

size_t				ft_strlen(const char *str);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlcat(char *dest, const char *src, size_t size);

void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				*free_ptr(void *ptr);
void				*ft_calloc(size_t count, size_t size);
void				ft_bzero(void *s, size_t n);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_skipallspace(const char *str, int *i);

char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strdup(const char *src);
char				*ft_strnstr(const char *str, const char *needle,
						size_t len);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
int					ft_strisnum(const char *str);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
#endif