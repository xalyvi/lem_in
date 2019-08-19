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

static t_node	*cr_node(size_t key)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->key = key;
	node->ant = 0;
	node->next = NULL;
	return (node);
}

static void		set_link(t_links *link, size_t key)
{
	t_node	*j;

	if (!(link->input))
	{
		link->input = cr_node(key);
		return ;
	}
	j = link->input;
	while (j)
	{
		if (j->key == key)
			return ;
		if (j->next == NULL)
		{
			j->next = cr_node(key);
			return ;
		}
		j = j->next;
	}
}

static int		find_graph(t_lem_in *lem_in, size_t dash)
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
		else if (!k && ft_strcmp(lem_in->rooms[i]->name,
		lem_in->line + dash + 1) == 0)
			k = lem_in->links + i;
		else if (j && k)
			break ;
		i++;
	}
	if (!j || !k)
		return (0);
	set_link(j, (size_t)(k - lem_in->links));
	set_link(k, (size_t)(j - lem_in->links));
	return (1);
}

static int		get_names(t_lem_in *lem_in)
{
	size_t	len1;
	size_t	len2;

	len1 = 0;
	while (lem_in->line[len1] != '\0' && lem_in->line[len1] != '-')
		len1++;
	len2 = len1 + 1;
	while (lem_in->line[len2] != '\0')
		len2++;
	len2 = len2 - len1 - 1;
	if (ft_strncmp(lem_in->line, lem_in->line + len1 + 1,
	((len1 > len2) ? len1 : len2)) == 0)
		return (0);
	return (find_graph(lem_in, len1));
}

int				get_links(t_lem_in *lem_in)
{
	lem_in->links = init_links(lem_in->count);
	if (!get_names(lem_in))
		return (free_error(lem_in, NULL, NULL));
	free(lem_in->line);
	while (get_line(&(lem_in->line)))
	{
		ft_putendl(lem_in->line);
		if (lem_in->line[0] == '#')
		{
			if (lem_in->line[1] == '#')
				if (ft_strcmp(lem_in->line, "##start") == 0 ||
				ft_strcmp(lem_in->line, "##end") == 0)
					return (free_error(lem_in, NULL, NULL));
		}
		else if (!get_names(lem_in))
			return (free_error(lem_in, NULL, NULL));
		free(lem_in->line);
	}
	lem_in->line = NULL;
	return (1);
}
