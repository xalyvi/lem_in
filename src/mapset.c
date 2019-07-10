#include "lem_in.h"
#include <stdio.h>

static void	find_i_fork(t_links *links, size_t s, size_t p)
{
	t_node	*node;
	t_node	*prev;

	while (links[s].o == 1)
	{
		p = s;
		s = links[s].input->key;
		if (links[s].level == 0)
			return ;
	}
	node = links[s].output;
	prev = NULL;
	while (node->key != p)
	{
		prev = node;
		node = node->next;
	}
	free(unlist(prev, node, &(links[s].output)));
	printf("\n");
	links[s].o--;
}

static void	deleto_input(t_links *links, size_t s)
{
	t_node	*node;

	node = links[s].input;
	while (node)
	{
		find_i_fork(links, node->key, s);
		node = node->next;
	}
}

static void	deleto_end(t_links *links, size_t s, size_t p)
{
	t_node	*node;
	t_node	*prev;

	prev = NULL;
	if (links[s].o > 1)
	{
		node = links[s].output;
		while (node->key != p)
		{
			prev = node;
			node = node->next;
		}
		free(unlist(prev, node, &(links[s].output)));
		links[s].o--;
		return ;
	}
	node = links[s].input;
	while (node)
	{
		deleto_end(links, node->key, s);
		node = node->next;
	}
}

void		deleto_links(t_lem_in *lem_in)
{
    size_t  i;
	size_t	j;

	j = 0;
	while (j < 3)
	{
		i = 0;
		while (i < lem_in->count)
		{
			if (i != lem_in->end && i != lem_in->start && lem_in->links[i].level > -1)
			{
				if (j == 0 && lem_in->links[i].o < 1)
					deleto_end(lem_in->links, i, 0);
				else if (j == 1 && lem_in->links[i].i > 1)
					deleto_input(lem_in->links, i);
				else if (j == 2 && lem_in->links, i)
					deleto_output(lem_in->links, i);
			}
			i++;
		}
		j++;
	}
}