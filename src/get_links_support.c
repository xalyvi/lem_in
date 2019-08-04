/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_links_support.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:13:34 by srolland          #+#    #+#             */
/*   Updated: 2019/05/30 12:14:41 by srolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_links			*init_links(size_t count)
{
	t_links	*links;
	size_t	i;

	links = (t_links *)malloc(sizeof(t_links) * count);
	i = 0;
	while (i < count)
	{
		links[i].level = -1;
		links[i].i = 0;
		links[i].o = 0;
		links[i].input = NULL;
		links[i].output = NULL;
		links[i].fl = 0;
		i++;
	}
	return (links);
}

static void		delete(t_links *links, size_t s, size_t p)
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
	unlist(prev, node, &(links[s].output));
	links[s].o--;
}

static void		from_start(t_links *links, size_t n, size_t start, size_t m)
{
	size_t	len;
	t_node	*node;
	t_node	*prev;
	size_t	s;
	size_t	p;

	node = links[n].input;
	prev = NULL;
	while (node)
	{
		if (node->key == m)
		{
			prev = node;
			node = node->next;
		}
		s = node->key;
		p = n;
		len = 1;
		while (s != start)
		{
			p = s;
			s = links[s].output->key;
			len++;
		}
		delete(links, s, p);
		unlist(node, prev, &(links[n].input));
		if (!prev)
			node = links[n].input;
		else
			prev->next = node->next;
		links[n].i--;
	}
}

static int	step_into_the_arena(t_links *links, size_t s, size_t p, size_t start, size_t *res)
{
	size_t	len;
	t_node	*node;
	t_node	*prev;

	len = 1;
	while (links[s].o < 2 || s != start)
	{
		p = s;
		s = links[s].output->key;
		len++;
	}
	if (s == start)
	{
		*res = len;
		return (0);
	}
	delete(links, s, p);
}

void			delete_any_other(t_links *links, size_t n, size_t start)
{
	size_t	m;
	t_node	*node;
	t_node	*prev;
	size_t	len;
	size_t	min;

	len = 0;
	node = links[n].input;
	prev = NULL;
	min = INT_MAX;
	while (node)
	{
		if (step_into_the_arena(links, node->key, n, start, &len))
		{
			unlist(node, prev, &(links[n].input));
			if (!prev)
				node = links[n].input;
			else
				node = prev->next;
			links[n].i--;
		}
		else
		{
			if (len < min)
			{
				min = len;
				m = node->key;
			}
			prev = node;
			node = node->next;
		}
	}
	if (links[n].i < 2)
		return ;
	from_start(links, n, start, m);
}
