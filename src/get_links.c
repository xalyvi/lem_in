#include "lem_in.h"
#include <stdio.h>

static int	free_lines(char *first, char *second, int ap)
{
	if (ap & 1)
		free(first);
	if (ap & 2)
		free(second);
	return (0);
}

static void	set_link(t_links *link, size_t a)
{
	t_node	*m;
	t_node	*j;

	m = (t_node *)malloc(sizeof(t_node));
	m->key = a;
	m->ant = 0;
	m->next = NULL;
	j = link->link;
	if (!j)
	{
		link->link = m;
		return ;
	}
	while (j->next)
		j = j->next;
	j->next = m;
}

static int	find_graph(t_lem_in *lem_in, char *first, char *second)
{
	size_t			i;
	t_links			*j;
	t_links			*k;

	i = 0;
	j = NULL;
	k = NULL;
	if (ft_strcmp(first, second) == 0)
		return (free_lines(first, second, 3));
	while (i < lem_in->count)
	{
		if (!j && ft_strcmp(lem_in->rooms[i]->name, first) == 0)
			j = lem_in->links + i;
		else if (!k && ft_strcmp(lem_in->rooms[i]->name, second) == 0)
			k = lem_in->links + i;
		else if (j && k)
			break ;
		i++;
	}
	if (!j && !k)
		return (free_lines(first, second, 3));
	set_link(j, (size_t)(k - lem_in->links));
	set_link(k, (size_t)(j - lem_in->links));
	return (1);
}

static int	get_names(t_lem_in *lem_in, char *line)
{
	char	*first;
	char	*second;
	int		i;

	i = 0;
	while(line[i] && line[i] != '-')
		i++;
	if (line[0] == 'L' || line[0] == '#' || line[i] != '-')
		return (0);
	if (!(first = ft_strsub(line, 0, i)))
		return (0);
	line = line + i + 1;
	i = 0;
	while (line[i])
		i++;
	if (line[0] == 'L' || line[0] == '#' ||!(second = ft_strsub(line, 0, i)))
		return (free_lines(first, NULL, 1));
	if (!find_graph(lem_in, first, second))
		return (0);
	free(first);
	free(second);
	return (1);
}

int			get_links(t_lem_in *lem_in)
{
	char	*line;

	lem_in->links = init_links(lem_in->count);
	if (!get_names(lem_in, lem_in->line))
	{
		free(lem_in->line);
		return (0);
	}
	free(lem_in->line);
	lem_in->line = NULL;
	while (get_line(&line))
	{
		ft_putendl(line);
		if (line[0] == '#')
		{
			if (line[1] == '#')
			{
				free(line);
				return (0);
			}
			free(line);
			continue;
		}
		get_names(lem_in, line);
		free(line);
	}
	return (1);
}