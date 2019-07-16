#include "lem_in.h"
#include <stdio.h>

static void	find_i_fork(t_links *links, size_t s, size_t p)
{
	t_node	*node;
	t_node	*prev;
	t_node	*fr;

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
	t_node	*tmp;

	if (links[s].o > 1)
	{
		prev = NULL;
		node = links[s].output;
		while (node->key != p)
		{
			prev = node;
			node = node->next;
		}
		if (!prev)
			links[s].output = node->next;
		else
			prev->next = node->next;
		free(node);
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

void		iterate_dead(t_links *links, size_t start)
{
	t_node	*node;

	if (links[start].level == INT_MAX)
		return ;
	if (links[start].o > 0)
	{
		node = links[start].output;
		while (node)
		{
			iterate_dead(links, node->key);
			node = node->next;
		}
		return ;
	}
	deleto_end(links, start, 0);
}

void		iterate_input(t_links *links, size_t start)
{
	t_node	*node;

	node = links[start].output;
	if (links[start].level == INT_MAX)
		return ;
	if (links[start].i > 1)
		deleto_input(links, start);
	node = links[start].output;
	while (node)
	{
		iterate_input(links, node->key);
		node = node->next;
	}
}