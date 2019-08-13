#include "lem_in.h"

static int	find_i_fork(t_links *links, size_t s, size_t p)
{
	t_node	*node;
	t_node	*prev;

	while (links[s].o == 1 && links[s].i > 0)
	{
		p = s;
		s = links[s].input->key;
		if (links[s].level == 0)
			return (1);
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
	return (0);
}

static void	deleto_input(t_links *links, size_t s, size_t start)
{
	t_node	*node;

	node = links[s].input;
	while (node)
	{
		if (find_i_fork(links, node->key, s))
		{
			delete_any_other(links, s, start);
			return ;
		}
		else
		{
			links[s].input = node->next;
			links[s].i--;
			free(node);
			node = links[s].input;
		}
	}
}

static void	deleto_end(t_links *links, size_t s, size_t p)
{
	t_node	*node;
	t_node	*prev;

	if (links[s].o > 1)
	{
		if (links[s].o > 2)
			links[s].fl = 1;
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

void	find_dead(t_links *links, size_t n, size_t start)
{
	if (links[n].o == 0)
		deleto_end(links, n, start);
}

void	find_i(t_links *links, size_t n, size_t start)
{
	if (links[n].i > 1)
		deleto_input(links, n, start);
}

static void	add_to_q(t_queue *q, t_links *links, char vis, size_t n)
{
	t_node	*node;

	node = links[n].output;
	while (node)
	{
		if (links[node->key].level < INT_MAX)
		{
			if (links[node->key].vis != vis)
			{
				enqueue(q, node->key);
				links[node->key].vis = vis;
			}
		}
		node = node->next;
	}
}

void		iterate(t_links *links, size_t start, char vis, void (*function)(t_links *links, size_t n, size_t start))
{
	size_t	n;

	t_queue	*q;
	q = create_queue();
	enqueue(q, start);
	while (!is_empty(q))
	{
		n = dequeue(q);
		if (links[n].level != INT_MAX)
		{
			if (n != start)
				(*function)(links, n, start);
			add_to_q(q, links, vis, n);
		}
	}
	free(q);

	// t_node	*node;

	// if (links[start].level == INT_MAX)
	// 	return ;
	// links[start].vis = 1;
	// if (links[start].o > 0)
	// {
	// 	node = links[start].output;
	// 	while (node)
	// 	{
	// 		if (links[node->key].vis != 1)
	// 			iterate_dead(links, node->key);
	// 		if (links[start].fl == 1)
	// 		{
	// 			node = links[start].output;
	// 			links[start].fl = 0;
	// 		}
	// 		else
	// 			node = node->next;
	// 	}
	// 	return ;
	// }
	// deleto_end(links, start, 0);
}

// void		iterate_input(t_links *links, size_t start, size_t s)
// {
// 	t_node	*node;

// 	if (links[start].vis == 2)
// 		return ;
// 	links[start].vis = 2;
// 	node = links[start].output;
// 	if (links[start].level == INT_MAX)
// 	{
// 		return ;
// 	}
// 	if (links[start].i > 1)
// 		deleto_input(links, start, s);
// 	node = links[start].output;
// 	while (node)
// 	{
// 		iterate_input(links, node->key, s);
// 		if (links[start].fl == 2)
// 		{
// 			links[start].fl = 1;
// 			node = links[start].output;
// 		}
// 		else
// 			node = node->next;
// 	}
// }