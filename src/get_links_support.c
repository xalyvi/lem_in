/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_links_support.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:13:34 by srolland          #+#    #+#             */
/*   Updated: 2019/05/30 12:14:41 by srolland         ###   ########.fr       */
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
		i++;
	}
	return (links);
}
