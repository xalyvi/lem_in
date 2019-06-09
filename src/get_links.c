/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:36:10 by srolland          #+#    #+#             */
/*   Updated: 2019/06/09 19:56:10 by srolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	set_link(t_links *link, size_t a)
{
	t_node	*m;
	t_node	*j;

	m = (t_node *)malloc(sizeof(t_node));
	m->key = a;
	m->ant = 0;
	m->next = NULL;
	j = link->link;
	if (!j)
	{
		link->link = m;
		return ;
	}
	while (j->next)
		j = j->next;
	j->next = m;
}

static int	find_graph(t_lem_in *lem_in, size_t	dash)
{
	size_t			i;
	t_links			*j;
	t_links			*k;

	i = 0;
	j = NULL;
	k = NULL;
	while (i < lem_in->count)
	{
		if (!j && ft_strncmp(lem_in->rooms[i]->name, lem_in->line, dash) == 0)
			j = lem_in->links + i;
		else if (!k && ft_strcmp(lem_in->rooms[i]->name, lem_in->line + dash + 1) == 0)
			k = lem_in->links + i;
		else if (j && k)
			break ;
		i++;
	}
	if (!j && !k)
		return (0);
	set_link(j, (size_t)(k - lem_in->links));
	set_link(k, (size_t)(j - lem_in->links));
	return (1);
}

static int	get_names(t_lem_in *lem_in)
{
	size_t	dash;

	dash = 0;
	while (lem_in->line[dash] != '\0' && lem_in->line[dash] != '-')
		dash++;
	if (ft_strncmp(lem_in->line, lem_in->line + dash + 1, dash) == 0)
		return (0);
	return (find_graph(lem_in, dash));
}

int			get_links(t_lem_in *lem_in)
{
	lem_in->links = init_links(lem_in->count);
	if (!get_names(lem_in))
		return (free_error(lem_in, NULL, NULL, NULL));
	free(lem_in->line);
	while (get_line(&(lem_in->line)))
	{
		ft_putendl(lem_in->line);
		if (lem_in->line[0] == '#')
		{
			if (lem_in->line[1] == '#')
				return (free_error(lem_in, NULL, NULL, NULL));
			free(lem_in->line);
			continue;
		}
		get_names(lem_in);
		free(lem_in->line);
	}
	return (1);
}
