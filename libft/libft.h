/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:42:35 by mukhairu          #+#    #+#             */
/*   Updated: 2023/06/23 12:03:01 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

//STRUCTURE LIST
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

//Part 1
// Returns 0 if the test character false, else return non-zero
int		ft_isalpha(int c);//any character for isupper(3)/islower(3) is true
int		ft_isdigit(int c); //tests for a decimal digit character
int		ft_isalnum(int c); //any charac for isalpha(3)/isdigit(3) istrue
int		ft_isascii(int c); //tests for an ASCII character, which is any
int		ft_isprint(int c); //tests for any printing character, including space

size_t	ft_strlen(const char *str); //returns the number of character 
void	*ft_memset(void *str, int c, size_t len); //returns its first argument
void	ft_bzero(void *s, size_t len); //writes n zeroed bytes to the string 
void	*ft_memcpy(void *dst, const void *src, size_t len);//copy
void	*ft_memmove(void *dst, const void *src, size_t len);//move w/out overlap
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);//done
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize); //done

int		ft_toupper(int c); //done
int		ft_tolower(int c); //done
char	*ft_strchr(const char *s, int c); //done
char	*ft_strrchr(const char *s, int c);//same like strchr but reverse
int		ft_strncmp(const char *s1, const char *s2, size_t n); //done
void	*ft_memchr(const void *s, int c, size_t n);// like strchr but w/ size
int		ft_memcmp(const void *s1, const void *s2, size_t n); //done
char	*ft_strnstr(const char *str, const char *to_find, size_t len);//done
int		ft_atoi(const char *str);//done

void	*ft_calloc(size_t count, size_t size); //just like malloc but mem is 0
char	*ft_strdup(const char *s1);//Done

//Part 2
//Malloc
char	*ft_substr(char const *s, unsigned int start, size_t len); //done
char	*ft_strjoin(char const *s1, char const *s2); //done
char	*ft_strtrim(char const *s1, char const *set);//done but unsure
char	**ft_split(char const *s, char c); //done maybe
char	*ft_itoa(int n); //
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char)); //done
void	ft_striteri(char *s, void (*f)(unsigned int, char*)); //Done

//file desciptor
void	ft_putchar_fd(char c, int fd);//done
void	ft_putstr_fd(char *s, int fd);//done
void	ft_putendl_fd(char *s, int fd);//done
void	ft_putnbr_fd(int n, int fd); //done

//Bonus files
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
