/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:12:09 by srolland          #+#    #+#             */
/*   Updated: 2019/05/30 12:15:02 by srolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static size_t	algol(t_paths **paths, size_t c)
{
	size_t	i;
	size_t	sum;

	sum = 0;
	i = 0;
	while (i < c)
	{
		sum += paths[c]->length - paths[i]->length;
		i++;
	}
	return (sum);
}

static size_t	move(t_paths *p, t_room **rooms, size_t m)
{
	t_node	*node;
	size_t	rt;

	rt = 0;
	node = p->path;
	if ((m > 0 && !(node->next)) || (node->next && node->next->ant > 0))
		rt++;
	while (node)
	{
		if (node->next)
			node->ant = node->next->ant;
		else
			node->ant = m;
		if (node->ant > 0)
		{
			write(1, "L", 1);
			ft_putnbr(node->ant);
			write(1, "-", 1);
			ft_putstr(rooms[node->key]->name);
			write(1, " ", 1);
		}
		node = node->next;
	}
	return (rt);
}

void			move_ants(t_lem_in *lem_in, t_paths **paths)
{
	size_t	c;
	size_t	i;
	size_t	m;
	size_t	end;

	c = lem_in->links[lem_in->start].o;
	m = 0;
	end = 0;
	while (end < lem_in->ants)
	{
		i = 0;
		while (i < c)
		{
			end += move(paths[i], lem_in->rooms, ((lem_in->ants - m > algol(paths, i)) ? ++m : 0));
			i++;
		}
		write(1, "\n", 1);
	}
}