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

// 4
// 3 2 2
// ##start
// start 4 0
// ##end
// end 4 6
// 4 0 4
// 1 4 2
// 2 4 4
// 5 8 2
// 6 8 4
// start-1
// 3-4
// 2-4
// 1-5
// 6-5
// end-6
// 1-2`
// 2-end
// 3-start

// L1-3
// L2-3 L1-4
// L3-3 L2-4 L1-2
// L4-3 L3-4 L2-2
// L4-4 L3-2
// L4-2

static void		check_ants(t_lem_in *lemin, t_node *tmp, size_t *i)
{
	while (tmp && ++lemin->l >= 0)
	{
		if (!tmp->next && tmp->ant)
			*i = *i + 1;
		else if (tmp->ant == 0 || !tmp->next)
		{
			tmp->ant = *i + 1;
			if (tmp->next && tmp->ant && lemin->l != 0)
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

void		move_ants(t_lem_in *lem_in, t_node *path)
{
	size_t 	i;

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