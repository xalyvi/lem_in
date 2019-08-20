/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 21:14:54 by srolland          #+#    #+#             */
/*   Updated: 2019/08/19 21:14:55 by srolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	*skip_comments(void)
{
	char	*line;

	line = NULL;
	while (get_line(&line) && line && line[0] == '#')
	{
		ft_putendl(line);
		if (line[1] == '#')
		{
			if (ft_strcmp(line, "##start") == 0 ||
			ft_strcmp(line, "##end") == 0)
			{
				free(line);
				return (NULL);
			}
		}
		free(line);
		line = NULL;
	}
	ft_putendl(line);
	return (line);
}

int		find_i_fork(t_links *links, size_t s, size_t p)
{
	t_node	*node;
	t_node	*prev;

	while (links[s].o == 1 && links[s].i > 0)
	{
		p = s;
		s = links[s].input->key;
		if (links[s].level == 0)
			return (1);
	}
	node = links[s].output;
	prev = NULL;
	while (node->key != p)
	{
		prev = node;
		node = node->next;
	}
	free(unlist(prev, node, &(links[s].output)));
	links[s].o--;
	return (0);
}
