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

static void	print_levels(t_lem_in *lem_in)
{
	t_links *link;
	t_node	*node;
	size_t	n;

	link = lem_in->links;
	n = 0;
	write(1, "\n\n", 2);
	while (n < lem_in->count)
	{
		printf("node: %s level: %d\n", lem_in->rooms[n]->name, lem_in->links[n].level);
		printf("\t inputs:");
		node = lem_in->links[n].link;
		while (node)
		{
			if (node->io == 1)
				printf(" %s", lem_in->rooms[node->key]->name);
			node = node->next;
		}
		printf("\n\toutputs:");
		node = lem_in->links[n].link;
		while (node)
		{
			if (node->io == 2)
				printf(" %s", lem_in->rooms[node->key]->name);
			node = node->next;
		}
		printf("\n");
		n++;
	}
}

int	main(void)
{
	char		*line;
	uintmax_t	ants;
	t_lem_in	*lem_in;

	ants = 0;
	line = NULL;
	get_line(&line);
	if (line)
		ft_putendl(line);
	if (line == NULL || !ft_isnumbers(line) || line[0] == '0')
		return (free_error(NULL, NULL, NULL, NULL));
	ants = ft_atoi(line);
	if (ants > 2147483647)
		return (free_error(NULL, NULL, NULL, NULL));
	free(line);
	if (!(lem_in = get_rooms()))
	{
		write(1, "\nreturn main (0)\n", 17);
		return (0);
	}
	lem_in->ants = ants;
	if (!get_links(lem_in))
		return (0);
	bfs(lem_in);
	print_levels(lem_in);
	write(1, "\n", 1);
	//move_ants(lem_in, path);
	return (0);
}
