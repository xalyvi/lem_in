#include "lem_in.h"

void    *free_all(t_lem_in *lem_in, t_node *list, int ap)
{
	t_node	*tmp;

	if (ap & 2 && list)
	{
		while (list)
		{
			if (ap & 16)
				free(list->name);
			if (ap & 8)
				free(list->list);
			tmp = list->next;
			free(list);
			list = tmp;
		}
	}
	if (ap & 4)
		free(lem_in->nodes);
	if (ap & 1)
		free(lem_in);
	return (NULL);
}

t_node	*free_node(t_node **node, char *line, int ap)
{
	if (ap & 1)
		free(line);
	if (ap & 2)
		free(*node);
	return (NULL);
}