/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 20:38:11 by srolland          #+#    #+#             */
/*   Updated: 2019/06/09 19:48:03 by srolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>

typedef struct	s_room
{
	char			*name;
	int				present;
	int				x;
	int				y;
	struct s_room	*next;
}				t_room;

typedef struct	s_node
{
	size_t			key;
	size_t			ant;
	size_t			io;
	size_t			i;
	size_t			o;
	struct s_node	*next;
}				t_node;

typedef struct	s_queue
{
	t_node *front;
	t_node *rear;
}				t_queue;

typedef struct	s_links
{
	unsigned char	flags;
	int				level;
	t_node			*link;
}				t_links;

typedef struct	s_lem_in
{
	size_t			count;
	char			*line;
	int				l;
	int				print;
	size_t			ants;
	size_t			start;
	size_t			end;
	unsigned char	flags;
	t_links			*links;
	t_room			**rooms;
}				t_lem_in;

t_queue			*create_queue(void);
void			enqueue(t_queue *q, int key);
size_t			dequeue(t_queue *q);
size_t			peek(t_queue *q);
int				is_empty(t_queue *q);

t_lem_in		*get_rooms();
void			*free_all(t_lem_in *lem_in, t_room *list, int ap);
int				check_room_er(t_lem_in *lem_in, t_room *node);
t_links			*init_links(size_t count);
int				get_links(t_lem_in *lem_in);
int				not_in(size_t k, t_node *n);
void			bfs(t_lem_in *lem_in);
void			move_ants(t_lem_in *lem_in, t_node *path);
int				check_points(t_lem_in *lem_in, size_t count, char *line, t_room *room);
int				free_error(t_lem_in *lem_in, t_room *room, char *line, t_node *path);

/*
**	UTILS
*/

int				get_line(char **line);
int				ft_isnumbers(const char *str);
uintmax_t		ft_atoi(const char *str);
void			ft_putchar(char c);
void			ft_putnbr(int nb);
void			ft_putstr(char *str);
void			ft_putendl(char *str);
int				str_digit(char *line);
char			*ft_strchr(char *s, int c);
size_t			ft_strlen(const char *str);
char			*ft_strdup(const char *str);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_strcmp(const char *s1, const char *s2);
int     		ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);

#endif
