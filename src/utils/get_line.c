/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:43:20 by srolland          #+#    #+#             */
/*   Updated: 2019/05/30 16:43:21 by srolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		read_from_fd(char **line)
{
	int		ret;
	char	*tmp;
	char	buf[2];

	while ((ret = read(0, buf, 1)))
	{
		buf[1] = '\0';
		tmp = *line;
		if (!(*line = ft_strjoin(*line, buf)))
			return (-1);
		free(tmp);
		if (buf[0] == '\n')
			break ;
	}
	return (ret);
}

int				get_line(char **line)
{
	char			buf[2];
	int				ret;
	char			*temp;
	char			*n;

	if (line == NULL || read(0, buf, 0) < 0)
		return (-1);
	temp = NULL;
	ret = read_from_fd(&temp);
	if (ret < 0 || !temp)
		return (0);
	*line = temp;
	n = ft_strchr(temp, '\n');
	if (n != NULL)
		n[0] = '\0';
	return (1);
}
