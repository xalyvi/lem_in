/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:32:14 by srolland          #+#    #+#             */
/*   Updated: 2019/06/09 20:05:29 by srolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_node *inlist(t_node *list, t_node *node)
{
	node->next = list;
	return (node);
}

t_node *unlist(t_node *prev, t_node *node, t_node **ls)
{
	if (!prev)
		*ls = node->next;
	else
		prev->next = node->next;
	return (node);
}

static void inner(t_links *links, t_node **node, t_node **prev, size_t i)
{
	if (links[(*node)->key].level == -1 || links[(*node)->key].level == links[i].level)
	{
		free(unlist(*prev, *node, &(links[i].input)));
		if (*prev)
			*node = (*prev)->next;
		else
			*node = links[i].input;
	}
	else if (links[i].level > links[(*node)->key].level)
	{
		links[i].i++;
		*prev = *node;
		*node = (*node)->next;
	}
	else if (links[i].level < links[(*node)->key].level)
	{
		links[i].output = inlist(links[i].output, unlist(*prev, *node, &(links[i].input)));
		links[i].o++;
		if (*prev)
			*node = (*prev)->next;
		else
			*node = links[i].input;
	}
}

static void input_output(t_lem_in *lem_in)
{
	size_t i;
	t_node *node;
	t_node *prev;

	i = 0;
	while (i < lem_in->count)
	{
		if (lem_in->links[i].level > -1)
		{
			prev = NULL;
			node = lem_in->links[i].input;
			while (node)
				inner(lem_in->links, &node, &prev, i);
		}
		i++;
	}
}

static int assign_levels(t_queue *q, t_lem_in *lem_in, size_t n)
{
	int end;
	t_node *node;

	end = 0;
	node = lem_in->links[n].input;
	while (node)
	{
		if (lem_in->links[node->key].level < 0)
		{
			enqueue(q, node->key);
			lem_in->links[node->key].level = lem_in->links[n].level + 1;
		}
		else if (lem_in->links[node->key].level == INT_MAX)
			end = 1;
		node = node->next;
	}
	return (end);
}

int bfs(t_lem_in *lem_in)
{
	t_queue *q;
	size_t n;
	int rt;

	q = create_queue();
	enqueue(q, lem_in->start);
	lem_in->links[lem_in->start].level = 0;
	lem_in->links[lem_in->end].level = INT_MAX;
	rt = 0;
	while (!is_empty(q))
	{
		n = dequeue(q);
		if (lem_in->links[n].level != INT_MAX)
			rt += assign_levels(q, lem_in, n);
	}
	free(q);
	if (!rt)
		return (free_error(lem_in, NULL, NULL));
	input_output(lem_in);
	iterate(lem_in->links, lem_in->start, 1, find_dead);
	iterate(lem_in->links, lem_in->start, 2, find_i);
	iterate_output(lem_in->links, lem_in->end, 3, find_o);
	return (1);
}