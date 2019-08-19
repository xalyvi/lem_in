/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 21:05:43 by srolland          #+#    #+#             */
/*   Updated: 2019/08/19 21:05:46 by srolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void		rotate_input_links(t_links *links, size_t s, size_t start)
{
	t_node	*node;

	node = links[s].input;
	while (node)
	{
		if (find_i_fork(links, node->key, s))
		{
			delete_any_other(links, s, start, 0);
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

static void	delete_dead_links(t_links *links, size_t s, size_t p)
{
	t_node	*node;
	t_node	*prev;

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
}

void		rotate_dead_links(t_links *links, size_t s, size_t p)
{
	t_node	*node;

	if (links[s].o > 1)
	{
		delete_dead_links(links, s, p);
		return ;
	}
	node = links[s].input;
	while (node)
	{
		rotate_dead_links(links, node->key, s);
		node = node->next;
	}
}

void		find_dead(t_links *links, size_t n, size_t start)
{
	if (links[n].o == 0)
		rotate_dead_links(links, n, start);
}

void		find_i(t_links *links, size_t n, size_t start)
{
	if (links[n].i > 1)
		rotate_input_links(links, n, start);
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

void		iterate(t_links *links, size_t start, char vis,
void (*function)(t_links *links, size_t n, size_t start))
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
}
