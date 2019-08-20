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

static void		print_ant(size_t ant, char *room)
{
	write(1, "L", 1);
	ft_putnbr(ant);
	write(1, "-", 1);
	ft_putstr(room);
}

static void		place_ant(t_node *node, size_t m)
{
	if (node->next)
		node->ant = node->next->ant;
	else
		node->ant = m;
}

static char		move(t_lem_in *lem_in, t_xy *sp, size_t m, char rp)
{
	t_node	*node;
	int		pr;
	char	rt;

	rt = 0;
	node = lem_in->paths[sp->p]->path;
	if ((m > 0 && !(node->next)) || (node->next && node->next->ant > 0))
		sp->start++;
	pr = 0;
	while (node)
	{
		place_ant(node, m);
		if (node->ant > 0)
		{
			if (pr || rp)
				write(1, " ", 1);
			rt = 1;
			print_ant(node->ant, lem_in->rooms[node->key]->name);
			pr = 1;
		}
		node = node->next;
	}
	return (rt);
}

void			move_ants(t_lem_in *lem_in)
{
	size_t	c;
	size_t	m;
	t_xy	sp;
	char	pr;

	c = lem_in->links[lem_in->start].o;
	m = 0;
	sp.start = 0;
	while (sp.start < lem_in->ants)
	{
		sp.p = 0;
		pr = 0;
		while (sp.p < c)
		{
			pr = move(lem_in, &(sp),
			((lem_in->ants - m > algol(lem_in->paths, sp.p)) ? ++m : 0), pr);
			sp.p++;
		}
		write(1, "\n", 1);
	}
}
