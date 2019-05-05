#include "lem_in.h"

static int	enter_nodes(t_lem_in *lem_in, t_node *node)
{
	int	i;

	if (!(lem_in->nodes = (t_node **)malloc(sizeof(t_node *) * (lem_in->count))))
	{
		free_all(lem_in, node, 19);
		return (1);
	}
	i = lem_in->count - 1;
	while (i > -1)
	{
		lem_in->nodes[i] = node;
		node = node->next;
		i--;
	}
	return (0);
}

void  	  	*free_all(t_lem_in *lem_in, t_node *list, int ap)
{
	t_node	*tmp;

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
		free(lem_in->nodes);
	if (ap & 8)
		free_links(lem_in->links);
	if (ap & 1)
		free(lem_in);
	return (NULL);
}

t_node		*free_node(t_node *node, char *line, int ap)
{
	if (ap & 1)
		free(line);
	if (ap & 2)
		free(node);
	return (NULL);
}

int			check_node_er(t_lem_in *lem_in, char *line, int count, t_node *node)
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
	if (enter_nodes(lem_in, node))
		return (1);
	return (0);
}