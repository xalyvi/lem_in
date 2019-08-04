/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:40:40 by srolland          #+#    #+#             */
/*   Updated: 2019/06/09 20:07:09 by srolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

void	print_paths(t_paths **paths, size_t size)
{
	size_t	i;
	t_node	*node;

	i = 0;
	while (i < size)
	{
		printf("path length: %zu\n", paths[i]->length);
		node = paths[i]->path;
		while (node)
		{
			if (node->next)
				printf("%zu->", node->key);
			else
				printf("%zu\n", node->key);
			node = node->next;
		}
		i++;
	}
}

void	print_levels(t_lem_in *lem_in)
{
	t_node	*node;
	size_t	n;

	n = 0;
	write(1, "\n\n", 2);
	printf("count: %zu, start: %zu, end: %zu\n", lem_in->count, lem_in->start, lem_in->end);
	/*
	while (n < lem_in->count)
	{
		printf("node: %s level: %d i: %zu o: %zu\n", lem_in->rooms[n]->name, lem_in->links[n].level, lem_in->links[n].i, lem_in->links[n].o);
		printf("\t inputs:");
		node = lem_in->links[n].input;
		while (node)
		{
			printf(" %s", lem_in->rooms[node->key]->name);
			node = node->next;
		}
		printf("\n\toutputs:");
		node = lem_in->links[n].output;
		while (node)
		{
			printf(" %s", lem_in->rooms[node->key]->name);
			node = node->next;
		}
		printf("\n");
		n++;
	}
	*/
}

int	main(void)
{
	char		*line;
	t_paths		**paths;
	size_t		ants;
	t_lem_in	*lem_in;

	ants = 0;
	line = NULL;
	get_line(&line);
	if (!line)
		return (free_error(NULL, NULL, NULL));
	while (line[0] == '#' && line[1] != '#')
	{
		if (!line)
			return (free_error(NULL, NULL, NULL));
		ft_putendl(line);
		free(line);
		line = NULL;
		get_line(&line);
	}
	ft_putendl(line);
	if (line == NULL || !ft_isnumbers(line) || line[0] == '0' || line[0] == '-')
		return (free_error(NULL, NULL, line));
	ants = ft_atoi(line);
	if (ants > 2147483647)
		return (free_error(NULL, NULL, NULL));
	free(line);
	if (!(lem_in = get_rooms()))
		return (0);
	lem_in->ants = ants;
	if (!get_links(lem_in))
		return (0);
	if (!bfs(lem_in))
		return (free_error(lem_in, NULL, NULL));
	paths = make_paths(lem_in->links, lem_in->start);
	// print_levels(lem_in);
	// print_paths(paths, lem_in->links[lem_in->start].o);
	write(1, "\n", 1);
	move_ants(lem_in, paths);
	free_all(lem_in, NULL, NULL, paths);
	return (0);
}
