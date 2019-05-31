/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:40:40 by srolland          #+#    #+#             */
/*   Updated: 2019/05/30 16:40:42 by srolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	main(void)
{
	char		*line;
	int			ants;
	t_lem_in	*lem_in;
	t_node		*path;

	ants = 0;
	line = NULL;
	get_line(&line);
	if (line == NULL || line[0] == '0')
		return (0);
	ants = ft_atoi(line);
	ft_putendl(line);
	free(line);
	if (!(lem_in = get_rooms()))
		return (0);
	lem_in->ants = ants;
	if (!get_links(lem_in))
		return (0);
	path = bfs(lem_in, 0);
	write(1, "\n", 1);
	move_ants(lem_in, path);
	return (0);
}
