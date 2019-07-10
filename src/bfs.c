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

// static void		to_path(t_node **path, size_t start)
// {
// 	t_node	*tmp;
// 	t_node	*n;

// 	tmp = *path;
// 	n = (t_node *)malloc(sizeof(t_node));
// 	n->key = start;
// 	n->next = NULL;
// 	if (!tmp)
// 	{
// 		*path = n;
// 		return ;
// 	}
// 	while (tmp && tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = n;
// }

// static int		shuffle_queue(t_lem_in *lem_in, t_node *tmp,
// 		t_queue *q, t_node *path)
// {
// 	while (tmp)
// 	{
// 		if (tmp->key == lem_in->end)
// 		{
// 			to_path(&path, tmp->key);
// 			return (1);
// 		}
// 		if (!lem_in->links[tmp->key].visited)
// 		{
// 			lem_in->links[tmp->key].visited = 1;
// 			enqueue(q, tmp->key);
// 			while (not_in(peek(q), tmp))
// 				enqueue(q, dequeue(q));
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

// static int		valid_path(t_node *path, size_t start, size_t end)
// {
// 	if (path->key != start)
// 		return (0);
// 	while (path && path->next)
// 		path = path->next;
// 	if (path->key != end)
// 		return (0);
// 	return (1);
// }

// static t_node	*ret(t_queue *q, t_node *path)
// {
// 	while (!is_empty(q))
// 		dequeue(q);
// 	free(q);
// 	return (path);
// }

// t_node			*bfs(t_lem_in *lem_in, size_t start)
// {
// 	t_node	*path;
// 	t_node	*tmp;
// 	t_node	*tmp2;
// 	t_queue	*q;

// 	path = NULL;
// 	start = lem_in->start;
// 	lem_in->links[start].visited = 1;
// 	q = create_queue();
// 	enqueue(q, start);
// 	while (!is_empty(q))
// 	{
// 		start = dequeue(q);
// 		to_path(&path, start);
// 		tmp = path;
// 		while (tmp)
// 			tmp = tmp->next;
// 		tmp2 = lem_in->links[start].link;
// 		if (shuffle_queue(lem_in, tmp2, q, path))
// 			return (ret(q, path));
// 	}
// 	if (!valid_path(path, lem_in->start, lem_in->end))
// 		return (!(free_error(lem_in, NULL, NULL, path)) ? NULL : NULL);
// 	free(q);
// 	return (path);
// }

static t_node	*inlist(t_node *list, t_node *node)
{
	node->next = list;
	return (node);
}

t_node	*unlist(t_node *prev, t_node *node, t_node **ls)
{
	if (!prev)
		*ls = node->next;
	else
		prev->next = node->next;
	return (node);
}


static void	input_output(t_lem_in *lem_in)
{
	size_t	i;
	t_node	*node;
	t_node	*prev;

	i = 0;
	while (i < lem_in->count)
	{
		if (lem_in->links[i].level > -1)
		{
			prev = NULL;
			node = lem_in->links[i].input;
			while (node)
			{
				if (lem_in->links[node->key].level == -1 || lem_in->links[node->key].level == lem_in->links[i].level)
				{
						free(unlist(prev, node, &(lem_in->links[i].input)));
						if (prev)
							node = prev->next;
						else
							node = lem_in->links[i].input;
				}
				else if (lem_in->links[i].level > lem_in->links[node->key].level)
				{
					lem_in->links[i].i++;
					prev = node;
					node = node->next;
				}
				else if (lem_in->links[i].level < lem_in->links[node->key].level)
				{
					lem_in->links[i].output = inlist(lem_in->links[i].output, unlist(prev, node, &(lem_in->links[i].input)));				
					lem_in->links[i].o++;
					if (prev)
						node = prev->next;
					else
						node = lem_in->links[i].input;
				}
			}
		}
		i++;
	}
}	

static void	assign_levels(t_queue *q,t_lem_in *lem_in, int n)
{
	t_node	*node;

	node = lem_in->links[n].input;
	while (node)
	{
		if (lem_in->links[node->key].level < 0)
		{
			enqueue(q, node->key);
			lem_in->links[node->key].level = lem_in->links[n].level + 1;
		}
		node = node->next;
	}
}

void	bfs(t_lem_in *lem_in)
{
	t_queue	*q;
	int		n;

	q = create_queue();
	enqueue(q, lem_in->start);
	lem_in->links[lem_in->start].level = 0;
	lem_in->links[lem_in->end].level = INT_MAX;
	while (!is_empty(q))
	{
		n = dequeue(q);
		if (lem_in->links[n].level != INT_MAX)
			assign_levels(q, lem_in, n);
	}
	free(q);
	input_output(lem_in);
	iterate_dead(lem_in->links, lem_in->start);
	iterate_input(lem_in->links, lem_in->start);
	iterate_output(lem_in->links, lem_in->end);
}