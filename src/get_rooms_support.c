#include "lem_in.h"

static int	enter_rooms(t_lem_in *lem_in, t_room *node)
{
	int	i;

	if (!(lem_in->rooms = (t_room **)malloc(sizeof(t_room *) * (lem_in->count))))
	{
		free_all(lem_in, node, 19);
		return (1);
	}
	i = lem_in->count - 1;
	while (i > -1)
	{
		lem_in->rooms[i] = node;
		node = node->next;
		i--;
	}
	return (0);
}

static void	free_links(t_links *links, size_t count)
{
	size_t	i;
	t_node	*m;

	i = 0;
	while (i < count)
	{
		m = links[i].link;
		while (m)
		{
			m = links[i].link->next;
			free(links[i].link);
		}
		i++;
	}
	free(links);
}

void  	  	*free_all(t_lem_in *lem_in, t_room *list, int ap)
{
	t_room	*tmp;

	if (ap & 2 && list)
	{
		while (list)
		{
			if (ap & 16)
				free(list->name);
			tmp = list->next;
			free(list);
			list = tmp;
		}
	}
	if (ap & 4)
		free(lem_in->rooms);
	if (ap & 8)
		free_links(lem_in->links, lem_in->count);
	if (ap & 1)
		free(lem_in);
	return (NULL);
}

t_room		*free_node(t_room *node, char *line, int ap)
{
	if (ap & 1)
		free(line);
	if (ap & 2)
		free(node);
	return (NULL);
}

int			check_node_er(t_lem_in *lem_in, char *line, int count, t_room *node)
{
	if (node == NULL || count < 1)
	{
		free_all(lem_in, NULL, 1);
		return (1);
	}
	if (!(lem_in->flags & 3))
	{
		free_all(lem_in, node, 19);
		return (1);
	}
	lem_in->count = count;
	if (line != NULL && ft_strchr(line, '-'))
		lem_in->line = line;
	else
	{
		free_all(lem_in, node, 19);
		free(line);
		return (1);
	}
	if (enter_rooms(lem_in, node))
		return (1);
	return (0);
}