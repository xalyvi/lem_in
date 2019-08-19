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
		links[i].vis = 0;
		i++;
	}
	return (links);
}

static void		delete(t_links *links, size_t p)
{
	t_node	*node;
	t_node	*prev;

	prev = NULL;
	node = links->output;
	while (node->key != p)
	{
		prev = node;
		node = node->next;
	}
	free(unlist(prev, node, &(links->output)));
	links->o--;
}

static void		free_node(t_node **node, t_node **prev, t_links *links)
{
	if (!*prev)
	{
		links->input = (*node)->next;
		free(*node);
		*node = links->input;
	}
	else
	{
		(*prev)->next = (*node)->next;
		free(*node);
		*node = (*prev)->next;
	}
	links->i--;
}

static void		from_start(t_links *links, size_t n, size_t start, size_t m)
{
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
		while (s != start)
		{
			p = s;
			s = links[s].input->key;
		}
		delete(links + s, p);
		free_node(&node, &prev, links + n);
		links[n].i--;
	}
}

static int		find_start_or_if(t_links *links, size_t s,
size_t p, size_t start, size_t *res)
{
	size_t	len;

	len = 1;
	while (links[s].o == 1 && links[s].i > 0 && s != start)
	{
		p = s;
		s = links[s].input->key;
		len++;
	}
	if (s == start)
	{
		*res = len;
		return (0);
	}
	delete(links + s, p);
	return (1);
}

void			delete_any_other(t_links *links, size_t n,
size_t start, size_t len)
{
	size_t	m;
	t_node	*node;
	t_node	*prev;
	size_t	min;

	node = links[n].input;
	prev = NULL;
	min = INT_MAX;
	while (node)
		if (find_start_or_if(links, node->key, n, start, &len))
			free_node(&node, &prev, links + n);
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
	if (links[n].i < 2)
		return ;
	from_start(links, n, start, m);
}
