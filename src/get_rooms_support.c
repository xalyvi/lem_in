/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms_support.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:42:08 by srolland          #+#    #+#             */
/*   Updated: 2019/06/09 19:55:00 by srolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lem_in	*init_lem_in(void)
{
	t_lem_in	*lem_in;

	if (!(lem_in = (t_lem_in *)malloc(sizeof(t_lem_in))))
		return (NULL);
	lem_in->start = 0;
	lem_in->flags = 0;
	lem_in->end = 0;
	lem_in->line = NULL;
	lem_in->links = NULL;
	lem_in->rooms = NULL;
	return (lem_in);
}

static int	enter_rooms(t_lem_in *lem_in, t_room *node)
{
	int	i;

	if (!(lem_in->rooms = (t_room **)malloc(sizeof(t_room *)
					* (lem_in->count))))
		return (free_error(lem_in, node, NULL));
	i = lem_in->count - 1;
	while (i > -1)
	{
		lem_in->rooms[i] = node;
		node = node->next;
		i--;
	}
	return (1);
}

int			check_room_er(t_lem_in *lem_in, t_room *room)
{
	t_room	*t;

	if (room && room->next)
	{
		t = room;
		room = room->next;
		while (room)
		{
			if (ft_strcmp(t->name, room->name) == 0 || (room->x == t->x && room->y == t->y))
				return (0);
			room = room->next;
		}
	}
	return (1);
}

int			check_points(t_lem_in *lem_in, size_t count, char *line, t_room *room)
{
	if (lem_in->flags != 3 || count < 2 || !line)
		return (free_error(lem_in, room, line));
	lem_in->count = count;
	lem_in->line = line;
	if (!enter_rooms(lem_in, room))
		return (0);
	return (1);
}
