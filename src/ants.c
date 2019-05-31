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
#include <unistd.h>

static void		print_ant(t_lem_in *lemin, t_node *tmp)
{
	if (lemin->print > 0)
		write(1, " ", 1);
	write(1, "L", 1);
	ft_putnbr(tmp->ant);
	write(1, "-", 1);
	ft_putstr(lemin->rooms[tmp->key]->name);
	++lemin->print;
}

static void		check_ants(t_lem_in *lemin, t_node *tmp, size_t *i)
{
	while (tmp && ++lemin->l >= 0)
	{
		if (!tmp->next && tmp->ant)
		{
			tmp->ant = *i + 1;
			print_ant(lemin, tmp);
			*i = *i + 1;
		}
		else if (tmp->ant == 0)
		{
			tmp->ant = *i + 1;
			if (!tmp->next)
				*i = *i + 1;
			if (tmp->ant && lemin->l != 0)
				print_ant(lemin, tmp);
			break ;
		}
		else
		{
			if (tmp->ant < lemin->ants)
			{
				tmp->ant = tmp->ant + 1;
				if (lemin->l != 0)
					print_ant(lemin, tmp);
			}
		}
		tmp = tmp->next;
	}
}

void			move_ants(t_lem_in *lem_in, t_node *path)
{
	size_t	i;

	i = 0;
	while (i != lem_in->ants)
	{
		lem_in->l = -1;
		lem_in->print = 0;
		check_ants(lem_in, path, &i);
		if (lem_in->print > 0)
			write(1, "\n", 1);
	}
}
