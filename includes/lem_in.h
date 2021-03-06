/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 20:38:11 by srolland          #+#    #+#             */
/*   Updated: 2019/08/20 18:48:08 by srolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>

typedef struct	s_xy
{
	size_t	p;
	size_t	start;
}				t_xy;

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
	struct s_node	*next;
}				t_node;

typedef struct	s_queue
{
	t_node *front;
	t_node *rear;
}				t_queue;

typedef struct	s_paths
{
	size_t	length;
	t_node	*path;
}				t_paths;

typedef struct	s_links
{
	int				level;
	size_t			i;
	size_t			o;
	t_node			*input;
	t_node			*output;
	char			vis;
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
	t_paths			**paths;
}				t_lem_in;

t_queue			*create_queue(void);
void			enqueue(t_queue *q, int key);
size_t			dequeue(t_queue *q);
size_t			peek(t_queue *q);
int				is_empty(t_queue *q);

t_lem_in		*init_lem_in(char **line, t_room **node, t_room **prev);
t_lem_in		*get_rooms();
void			*skip_comments();
void			free_all(t_lem_in *lem_in, t_room *room, char *line,
		t_paths **paths);
int				check_coord(char const *line, int for_what);
int				check_room_er(t_room *node);
t_links			*init_links(size_t count);
void			rotate_dead_links(t_links *links, size_t s, size_t p);
void			rotate_input_links(t_links *links, size_t s, size_t start);
int				get_links(t_lem_in *lem_in);
int				bfs(t_lem_in *lem_in);
void			iterate(t_links *links, size_t start, char vis,
		void (*function)(t_links *links, size_t n, size_t start));
void			iterate_output(t_links *links, size_t start, char vis,
		void (*function)(t_links *links, size_t n));
void			find_dead(t_links *links, size_t n, size_t start);
void			find_i(t_links *links, size_t n, size_t start);
void			find_o(t_links *links, size_t n);
void			compare_to_in(size_t cur, size_t *len, t_node *temp,
		t_node **node);
int				check_points(t_lem_in *lem_in, size_t count, char *line,
		t_room *room);
int				free_error(t_lem_in *lem_in, t_room *room, char *line);
t_node			*unlist(t_node *prev, t_node *node, t_node **ls);
int				find_i_fork(t_links *links, size_t s, size_t p);
void			delete_any_other(t_links *links, t_xy sp, size_t len);
t_paths			**make_paths(t_links *links, size_t start);
void			move_ants(t_lem_in *lem_in);

/*
**	UTILS
*/

int				get_line(char **line);
int				ft_isnumbers(const char *str);
long			ft_atoi(const char *str);
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
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);

#endif
