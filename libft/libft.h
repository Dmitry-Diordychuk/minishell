/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 18:50:18 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/26 20:48:50 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include "get_next_line.h"

# define TRUE 1
# define FALSE 0

typedef int			t_bool;

/*
** Memory
*/

void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *b, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

/*
** Memory allocation
*/

void				*ft_malloc(size_t size, size_t *ret_counter);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_strdup_between(const char *start, const char *end);
size_t				ft_free(void *ptr);

/*
** String
*/

size_t				ft_strlen(const char *str);
char				*ft_strcpy(char *dst, const char *src);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strpbrk(const char *s, const char *charset);
char				*ft_strtok(char *string, const char *delim);

char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strtrim_head(char const *s1, char const *set);
char				*ft_strtrim_tail(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_strrotate(char *str);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/*
** Convert in string and out of string
*/

int					ft_atoi(const char *str);
char				*ft_itoa(int n);
double				ft_atof(const char *str);

/*
** Check char
*/

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_isset(char c, char const *set);

/*
** Modify char
*/

int					ft_toupper(int c);
int					ft_tolower(int c);

/*
** Output
*/

int					ft_putchar(int c);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putunbr_fd(unsigned int n, int fd);

/*
** List single
*/

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				*ft_lstget(t_list *list, int number);
void				ft_lstpush(t_list **list, t_list *elem);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void*));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
												void (*del)(void *));
t_list				*ft_lstfind(t_list *list, void *data_ref, int (*cmp)());

/*
** List double
*/

typedef struct		s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
	t_bool			sorted;
}					t_dlist;

typedef struct		s_diter
{
	struct s_dlist	**list;
	struct s_dlist	*cur;
}					t_diter;

typedef void*		t_ddata;
typedef t_dlist*	t_delement;
typedef void		(*t_ddelfunc)(t_ddata);
typedef int			(*t_dcompfunc)(t_ddata, t_ddata);
typedef t_bool		(*t_dequlfunc)(t_ddata, t_ddata);

t_delement			ft_dlst_new(t_ddata data);
void				ft_dlst_del(t_delement elem, t_ddelfunc del);

void				ft_dlst_append(t_dlist **dlst, t_delement elem);
void				ft_dlst_prepend(t_dlist **dlst, t_delement elem);
t_bool				ft_dlst_insert(t_dlist **dlst, t_delement elem, int n);

t_ddata				ft_dlst_getfirst_data(t_dlist *list);
t_delement			ft_dlst_getfirst_elem(t_dlist *list);
t_ddata				ft_dlst_getlast_data(t_dlist *list);
t_delement			ft_dlst_getlast_elem(t_dlist *list);
t_ddata				ft_dlst_getnth_data(t_dlist *list, size_t n);
t_delement			ft_dlst_getnth_elem(t_dlist *list, size_t n);

t_ddata				ft_dlst_popfirst_data(t_dlist **list);
t_delement			ft_dlst_popfirst_elem(t_dlist **list);
t_ddata				ft_dlst_poplast_data(t_dlist **list);
t_delement			ft_dlst_poplast_elem(t_dlist **list);
t_ddata				ft_dlst_popnth_data(t_dlist **list, size_t n);
t_delement			ft_dlst_popnth_elem(t_dlist **list, size_t n);

t_bool				ft_dlst_removefirst(t_dlist **list, t_ddelfunc del);
t_bool				ft_dlst_removelast(t_dlist **list, t_ddelfunc del);
t_bool				ft_dlst_removenth(t_dlist **list, t_ddelfunc del, size_t n);
void				ft_dlst_unlink_elem(t_delement elem);
void				ft_dlst_clear(t_dlist **dlst, t_ddelfunc del);
t_dlist				*ft_dlst_dup(t_dlist *list, size_t sizeof_content,
															t_ddelfunc del);

size_t				ft_dlst_size(t_dlist *lst);
void				ft_dlst_sort(t_dlist **list, t_dcompfunc comp);
t_delement			ft_dlst_find(t_dlist *list, t_dequlfunc equl, t_ddata data);

void				ft_diter_init(t_dlist **list, t_diter *iter);
t_bool				ft_diter_more(t_diter *iter);
t_ddata				ft_diter_getnext(t_diter *iter);
void				ft_diter_remove(t_diter *iter, t_ddelfunc del);

#endif
