#include "lem_in.h"

static int	free_lines(char *first, char *second, int ap)
{
	if (ap & 1)
		free(first);
	if (ap & 2)
		free(second);
	return (0);
}

static void	set_link(t_lem_in *lem_in, int a, int b)
{
	int	i;

	if (lem_in->nodes[a]->list == NULL)
	{
		lem_in->nodes[a]->list = (int *)malloc(sizeof(int) * lem_in->count);
		i = -1;
		while (++i < lem_in->count)
			lem_in->nodes[a]->list[i] = -1;
	}
	if (lem_in->nodes[b]->list == NULL)
	{
		lem_in->nodes[b]->list = (int *)malloc(sizeof(int) * lem_in->count);
		i = -1;
		while (++i < lem_in->count)
			lem_in->nodes[b]->list[i] = -1;
	}
	i = 0;
	while (lem_in->nodes[a]->list[i] != -1 && lem_in->nodes[a]->list[i] != b)
		i++;
	lem_in->nodes[a]->list[i] = b;
	lem_in->nodes[a]->neigh++;
	i = 0;
	while (lem_in->nodes[b]->list[i] != -1 && lem_in->nodes[b]->list[i] != a)
		i++;
	lem_in->nodes[b]->list[i] = a;
}

static int	find_graph(t_lem_in *lem_in, char *first, char *second)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = -1;
	k = -1;
	if (ft_strcmp(first, second) == 0)
		return (free_lines(first, second, 3));
	while (lem_in->nodes[i])
	{
		if (ft_strcmp(lem_in->nodes[i]->name, first) == 0)
			j = i;
		else if (ft_strcmp(lem_in->nodes[i]->name, second) == 0)
			k = i;
		if (j > -1 && k > -1)
			break ;
		i++;
	}
	if (j < 0 || k < 0)
		return (free_lines(first, second, 3));
	set_link(lem_in, j, k);
	lem_in->nodes[k]->neigh++;
	return (1);
}

static int	get_names(t_lem_in *lem_in, char *line)
{
	char	*first;
	char	*second;
	int		i;

	i = 0;
	while(line[i] && line[i] != '-')
		i++;
	if (line[0] == 'L' || line[0] == '#' || line[i] != '-')
		return (0);
	if (!(first = ft_strsub(line, 0, i)))
		return (0);
	line = line + i + 1;
	i = 0;
	while (line[i])
		i++;
	if (line[0] == 'L' || line[0] == '#' ||!(second = ft_strsub(line, 0, i)))
		return (free_lines(first, NULL, 1));
	if (!find_graph(lem_in, first, second))
		return (0);
	free(first);
	free(second);
	return (1);
}

int			get_links(t_lem_in *lem_in)
{
	char	*line;

	if (!get_names(lem_in, lem_in->line))
	{
		free(lem_in->line);
		return (0);
	}
	free(lem_in->line);
	lem_in->line = NULL;
	while (get_line(&line))
	{
		if (line[0] == '#')
		{
			if (line[1] == '#')
			{
				free(line);
				return (0);
			}
			free(line);
			continue;
		}
		get_names(lem_in, line);
		free(line);
	}
	return (1);
}