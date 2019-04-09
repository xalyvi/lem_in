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
**
*/

typedef struct	s_node
{
	char			*name;
	int				x;
	int				y;
	int				*list;
	struct s_node	*next;
}				t_node;

typedef struct	s_lem_in
{
	int		start;
	int		end;
	t_node	*nodes[];
}				t_lem_in;

t_lem_in    	*get_nodes();
void    		*free_all(t_lem_in *lem_in, t_node *list, int ap);
t_node			*free_node(t_node **node, char *line, int ap);


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