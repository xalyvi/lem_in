/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_sup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 17:44:33 by srolland          #+#    #+#             */
/*   Updated: 2019/08/20 17:44:34 by srolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_links	*init_links(size_t count)
{
	t_links	*links;
	size_t	i;

	links = (t_links *)malloc(sizeof(t_links) * count);
	i = 0;
	while (i < count)
	{
		links[i].level = -1;
		links[i].i = 0;
		links[i].o = 0;
		links[i].input = NULL;
		links[i].output = NULL;
		links[i].vis = 0;
		i++;
	}
	return (links);
}

t_node	*unlist(t_node *prev, t_node *node, t_node **ls)
{
	if (!prev)
		*ls = node->next;
	else
		prev->next = node->next;
	return (node);
}

void	compare_to_in(size_t cur, size_t *len, t_node *temp, t_node **node)
{
	if (cur < *len)
	{
		*len = cur;
		*node = temp;
	}
}

void	find_dead(t_links *links, size_t n, size_t start)
{
	if (links[n].o == 0)
		rotate_dead_links(links, n, start);
}

void	find_i(t_links *links, size_t n, size_t start)
{
	if (links[n].i > 1)
		rotate_input_links(links, n, start);
}
