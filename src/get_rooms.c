/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:38:27 by srolland          #+#    #+#             */
/*   Updated: 2019/06/09 20:21:30 by srolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_lem_in	*init(void)
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

static int		get_coord(char *line, t_room *node)
{
	if (*line == '\0' || *(line + 1) == '\0' ||
			(*(line + 1) == '0' && *(line + 2) != ' '))
		return (0);
	else
		node->x = ft_atoi(++line);
	while (*line >= '0' && *line <= '9')
		line++;
	if (*line == '\0' || *(line + 1) == '\0' ||
			(*(line + 1) == '0' && *(line + 2) != '\0'))
		return (0);
	else
		node->y = ft_atoi(++line);
	while (*line >= '0' && *line <= '9')
		line++;
	if (*line == '\0')
		return (1);
	return (0);
}

static t_room	*get_room(char *line, t_room **prev, size_t *count)
{
	t_room	*node;
	size_t	name;

	name = 0;
	if (line[0] == 'L')
		return (NULL);
	while (line[name] != ' ' && line[name] != '\0')
		name++;
	if (line[name] == '\0')
		return (NULL);
	if (!(node = (t_room *)malloc(sizeof(t_room))))
		return (NULL);
	node->name = ft_strsub(line, 0, name);
	if (!get_coord(line + name, node))
	{
		free(node);
		return (NULL);
	}
	node->next = *prev;
	*prev = node;
	*count += 1;
	return (node);
}

static int		get_start_end(char **line, t_lem_in *lem_in,
		int count)
{
	if (line[0][1] == '#')
	{
		if (ft_strcmp(*line, "##start") == 0)
		{
			if (!(lem_in->flags & 1) && (lem_in->flags |= 1))
				lem_in->start = count;
			else
				return (1);
		}
		else if (ft_strcmp(*line, "##end") == 0)
		{
			if (!(lem_in->flags & 2) && (lem_in->flags |= 2))
				lem_in->end = count;
			else
				return (1);
		}
	}
	free(*line);
	get_line(line);
	ft_putendl(*line);
	return (0);
}

t_lem_in		*get_rooms(void)
{
	char		*line;
	t_lem_in	*lem_in;
	t_room		*node;
	t_room		*prev;
	size_t		count;

	if (!(lem_in = init()))
		return (NULL);
	count = 0;
	prev = NULL;
	while (get_line(&line))
	{
		ft_putendl(line);
		if (ft_strchr(line, '-'))
			break ;
		if (line[0] == '#')
			if (get_start_end(&line, lem_in, count))
				return ((!free_error(lem_in, prev, line, NULL)) ? NULL : NULL);
		if (!(node = get_room(line, &prev, &count)))
			return ((!free_error(lem_in, prev, line, NULL)) ? NULL : NULL);
		free(line);
		if (!check_room_er(lem_in, node))
			return (NULL);
		line = NULL;
	}
	if (!check_points(lem_in, count, line, node))
		return (NULL);
	return (lem_in);
}
