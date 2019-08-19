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

/*
**	TODO: '\n' at the end of lines
**	TODO: norminette
**	TODO: author file
**	TODO: strerror() and perror()
**
**	maps to check:
**
**	mpps/maps/illegalname1
**
**	@(bad path trimming)
**	/mpps/maps3/subject_map
**	/test/test1
**	/test/test7
**	test_ing/maps/in0
**	test_ing/maps/input1
**	test_ing/maps/map42
**
**	Solution: it's all random! :)
*/

static char	*read_ants_number(void)
{
	char	*line;

	line = NULL;
	if (!(line = skip_comments()))
		return (free_error(NULL, NULL, NULL) ? NULL : NULL);
	if (line == NULL || !ft_isnumbers(line) || line[0] == '0' || line[0] == '-')
		return (free_error(NULL, NULL, line) ? NULL : NULL);
	return (line);
}

int			main(void)
{
	char		*line;
	t_paths		**paths;
	size_t		ants;
	t_lem_in	*lem_in;

	ants = 0;
	line = NULL;
	if (!(line = read_ants_number()))
		return (0);
	ants = ft_atoi(line);
	if (ants > 2147483647)
		return (free_error(NULL, NULL, NULL));
	free(line);
	if (!(lem_in = get_rooms(0)))
		return (0);
	lem_in->ants = ants;
	if (!get_links(lem_in))
		return (0);
	if (!bfs(lem_in))
		return (0);
	paths = make_paths(lem_in->links, lem_in->start);
	write(1, "\n", 1);
	move_ants(lem_in, paths);
	free_all(lem_in, NULL, NULL, paths);
	return (0);
}
