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

static void	free_rooms(t_room **rooms, size_t size)
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

static void	free_links(t_links *links, size_t size)
{
	size_t i;
	t_node *t_link;

	if (!links)
		return ;
	i = 0;
	while (i < size)
	{
		while (links[i].input)
		{
			t_link = links[i].input->next;
			free(links[i].input);
			links[i].input = t_link;
		}
		while (links[i].output)
		{
			t_link = links[i].output->next;
			free(links[i].output);
			links[i].output = t_link;
		}
		i++;
	}
	free(links);
}

static void	free_path(t_paths **paths, size_t s)
{
	t_node	*node;
	t_node	*tmp;
	size_t	i;

	i = 0;
	while (i < s)
	{
		node = paths[i]->path;
		while (node)
		{
			tmp = node->next;
			free(node);
			node = tmp;
		}
		free(paths[i]);
		i++;
	}
	free(paths);
}

void		free_all(t_lem_in *lem_in, t_room *room,
char *line, t_paths **paths)
{
	t_room	*temp;

	if (line)
		free(line);
	if (room)
		while (room)
		{
			temp = room->next;
			if (room->name)
				free(room->name);
			free(room);
			room = temp;
		}
	if (paths)
		free_path(paths, lem_in->links[lem_in->start].o);
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
}

int			free_error(t_lem_in *lem_in, t_room *room, char *line)
{
	free_all(lem_in, room, line, NULL);
	write(2, "ERROR\n", 6);
	return (0);
}
