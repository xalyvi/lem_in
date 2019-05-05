#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>


/*
**	LEM_IN
**
**		lem_in		1
**		nodes[]		2
**		nodes		4
**		nodes->list	8
**		nodes->name	16
**
**
**		NOTES:
**
**
**
**
**
**
*/

typedef struct	s_node
{
	char			*name;
	int				present;
	int				x;
	int				y;
	struct s_node	*next;
}				t_node;

typedef struct	s_qnode
{
	size_t		key;
	size_t		ant;
	struct s_qnode	*next;
}				t_qnode;

typedef struct	s_queue
{
	t_qnode *front;
	t_qnode *rear;
	size_t	size;
}				t_queue;

typedef struct	s_links
{
	unsigned char	flags;
	unsigned char	visited;
	t_qnode			*link;
}				t_links;

typedef struct	s_lem_in
{
	size_t			count;
	int				max_edge;
	int				ants;
	size_t			start;
	size_t			end;
	unsigned char	flags;
	char			*line;
	t_links			*links;
	t_node			**nodes;
}				t_lem_in;

t_queue			*create_queue(void);
void			add_qnode(t_queue *q, int key);
void			delete_qnode(t_queue *q);
void    		fill_array(int distance[], int count);

t_lem_in    	*get_nodes();
void    		*free_all(t_lem_in *lem_in, t_node *list, int ap);
t_node			*free_node(t_node *node, char *line, int ap);
int				check_node_er(t_lem_in *lem_in, char *line, int count, t_node *node);
t_links   		*init_links(size_t count);
int				get_links(t_lem_in *lem_in);
void			solve_lem_in(t_lem_in *lem_in);


/*
**	UTILS
*/

int				get_line(char **line);
int				ft_atoi(const char *str);
int				str_digit(char *line);
char			*ft_strchr(char *s, int c);
size_t			ft_strlen(const char *str);
char			*ft_strdup(const char *str);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strsub(char const *s, unsigned int start, size_t len);

#endif