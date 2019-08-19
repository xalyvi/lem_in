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
