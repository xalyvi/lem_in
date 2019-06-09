/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 17:29:14 by srolland          #+#    #+#             */
/*   Updated: 2019/06/09 20:22:45 by srolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void free_rooms(t_room **rooms, size_t size)
{
	size_t i;

	if (!rooms || !rooms[0])
		return ;
	i = 0;
	while (i < size)
	{
		if (rooms[i]->name)
			free(rooms[i]->name);
		free(rooms[i]);
		i++;
	}
	free(rooms);
}

static void free_links(t_links *links, size_t size)
{
	size_t i;
	t_node *t_link;

	if (!links)
		return ;
	i = 0;
	while (i < size)
	{
		while (links[i].link)
		{
			t_link = links[i].link->next;
			free(links[i].link);
			links[i].link = t_link;
		}
		i++;
	}
	free(links);
}

static void free_path(t_node *path)
{
	t_node *temp;

	while (path)
	{
		temp = path->next;
		free(path);
		path = temp;
	}
}

int			free_error(t_lem_in *lem_in, t_room *room, char *line, t_node *path)
{
	t_room *t_room;

	if (line)
		free(line);
	if (room)
		while (room)
		{
			t_room = room->next;
			if (room->name)
				free(room->name);
			free(room);
			room = t_room;
		}
	if (lem_in)
	{
		if (lem_in->rooms)
			free_rooms(lem_in->rooms, lem_in->count);
		if (lem_in->links)
			free_links(lem_in->links, lem_in->count);
		if (lem_in->line)
			free(lem_in->line);
		free(lem_in);
	}
	if (path)
		free_path(path);
	write(1, "error\n", 6);
	return (0);
}
