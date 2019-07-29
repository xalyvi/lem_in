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
# include <stdint.h>
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
	char			fl;
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
	char			*vis;
	t_links			*links;
	t_room			**rooms;
}				t_lem_in;

t_queue			*create_queue(void);
void			enqueue(t_queue *q, int key);
size_t			dequeue(t_queue *q);
size_t			peek(t_queue *q);
int				is_empty(t_queue *q);

t_lem_in		*init_lem_in(void);
void			vis_zer(char *vis, size_t n);
t_lem_in		*get_rooms();
void			free_all(t_lem_in *lem_in, t_room *room, char *line, t_paths **paths);
int				check_coord(char const *line, int for_what);
int				check_room_er(t_lem_in *lem_in, t_room *node);
t_links			*init_links(size_t count);
int				get_links(t_lem_in *lem_in);
int				bfs(t_lem_in *lem_in);
int				check_points(t_lem_in *lem_in, size_t count, char *line, t_room *room);
int				free_error(t_lem_in *lem_in, t_room *room, char *line);
t_node			*unlist(t_node *prev, t_node *node, t_node **ls);
void			iterate_dead(t_links *links, char *vis, size_t start);
void			iterate_input(t_links *links, size_t start);
void   			iterate_output(t_links *links, size_t start);
t_paths			**make_paths(t_links *links, size_t start);
void			move_ants(t_lem_in *lem_in, t_paths **paths);

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
int     		ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);

#endif
