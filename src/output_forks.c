/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 21:08:12 by srolland          #+#    #+#             */
/*   Updated: 2019/08/19 21:08:14 by srolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	free_if(t_links *links, t_node **node, t_node **prev)
{
	if (!*prev)
	{
		links->output = (*node)->next;
		free(*node);
		*node = links->output;
	}
	else
	{
		(*prev)->next = (*node)->next;
		free(*node);
		*node = (*prev)->next;
	}
}

static void	delete_others(t_links *links, size_t key, t_node *save)
{
	t_node *node;
	t_node *prev;

	prev = NULL;
	node = links[key].output;
	while (node)
	{
		if (node != save)
		{
			free_if(links + key, &node, &prev);
			links[key].o--;
		}
		else
		{
			prev = node;
			node = node->next;
		}
	}
}

void		find_o(t_links *links, size_t n)
{
	t_node *node;
	t_node *temp;
	size_t key;
	size_t len;
	size_t cur;

	if (links[n].o > 1)
	{
		len = INT_MAX;
		temp = links[n].output;
		while (temp)
		{
			cur = 1;
			key = temp->key;
			while (links[key].level != INT_MAX)
			{
				key = links[key].output->key;
				cur++;
			}
			compare_to_in(cur, &len, temp, &node);
			temp = temp->next;
		}
		delete_others(links, n, node);
	}
}

static void	add_to_q(t_queue *q, t_links *links, char vis, size_t n)
{
	t_node *node;

	node = links[n].input;
	while (node)
	{
		if (links[node->key].level > 0)
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

void		iterate_output(t_links *links, size_t start, char vis,
void (*function)(t_links *links, size_t n))
{
	size_t	n;
	t_queue *q;

	q = create_queue();
	enqueue(q, start);
	while (!is_empty(q))
	{
		n = dequeue(q);
		if (links[n].level != 0)
		{
			if (n != start)
				(*function)(links, n);
			add_to_q(q, links, vis, n);
		}
	}
	free(q);
}
