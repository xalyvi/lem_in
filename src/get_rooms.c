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

static int		get_coord(char const *line, t_room *node)
{
	long	n;

	if (!check_coord(line, 1))
		return (0);
	else
		n = ft_atoi(line);
	if (n > INT_MAX || n < INT_MIN)
		return (0);
	node->x = n;
	while ((*line >= '0' && *line <= '9') || *line == '-')
		line++;
	line++;
	if (!check_coord(line, 2))
		return (0);
	else
		n = ft_atoi(line);
	if (n > INT_MAX || n < INT_MIN)
		return (0);
	node->y = n;
	return (1);
}

static t_room	*get_room(char const *line, t_room **prev, size_t *count)
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
	if (*(line + name) != ' ' || !get_coord(line + name + 1, node))
	{
		free(node->name);
		free(node);
		return (NULL);
	}
	node->next = *prev;
	*prev = node;
	*count += 1;
	return (node);
}

static t_room	*inroom(t_room **prev, const char *line, size_t *count)
{
	t_room	*room;

	if (!(room = get_room(line, prev, count)))
		return (NULL);
	else if (!check_room_er(room))
		return (NULL);
	return (room);
}

static t_room	*get_start_end(char **line, t_lem_in *lem_in,
		size_t *count, t_room **prev)
{

	if (ft_strcmp(*line, "##start") == 0)
	{
		if (!(lem_in->flags & 1) && (lem_in->flags |= 1))
			lem_in->start = *count;
		else
			return (NULL);
	}
	else if (ft_strcmp(*line, "##end") == 0)
	{
		if (!(lem_in->flags & 2) && (lem_in->flags |= 2))
			lem_in->end = *count;
		else
			return (NULL);
	}
	else
		return (NULL);
	free(*line);
	get_line(line);
	ft_putendl(*line);
	return (inroom(prev, *line, count));
}

t_lem_in		*get_rooms(void)
{
	char		*line;
	t_lem_in	*lem_in;
	t_room		*node;
	t_room		*prev;
	size_t		count;

	if (!(lem_in = init_lem_in()))
		return (NULL);
	count = 0;
	prev = NULL;
	node = NULL;
	while (get_line(&line))
	{
		ft_putendl(line);
		if (ft_strchr(line, '-'))
			break ;
		if (line[0] == '#')
		{
			if (line[1] == '#' && !(node = get_start_end(&line, lem_in, &count, &prev)))
				return ((!free_error(lem_in, prev, line)) ? NULL : NULL);
		}
		else if (!(node = inroom(&prev, line, &count)))
			return ((!free_error(lem_in, prev, line)) ? NULL : NULL);
		free(line);
		line = NULL;
	}
	if (!check_points(lem_in, count, line, node))
		return (NULL);
	return (lem_in);
}
