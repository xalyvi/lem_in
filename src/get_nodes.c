#include "lem_in.h"

static t_lem_in	*init(void)
{
	t_lem_in	*lem_in;

	if (!(lem_in = (t_lem_in *)malloc(sizeof(t_lem_in))))
		return (NULL);
	lem_in->start = 0;
	lem_in->flags = 0;
	lem_in->end = 0;
	lem_in->line = NULL;
	return (lem_in);
}

static char		*get_coord(char *line, t_node *node)
{
	if (*line == '\0' || *(line + 1) == '\0' || (*(line + 1) == '0' && *(line + 2) != ' '))
		return (NULL);
	else
		node->x = ft_atoi(++line);
	while (*line >= '0' && *line <= '9')
		line++;
	if (*line == '\0' || *(line + 1) == '\0' || (*(line + 1) == '0' && *(line + 2) != '\0'))
		return (NULL);
	else
		node->y = ft_atoi(++line);
	while (*line >= '0' && *line <= '9')
		line++;
	if (*line == '\0')
		return (line);
	return (NULL);
}

static t_node	*get_node(char *line, t_node **prev, int *count)
{
	t_node	*node;
	size_t	name;

	name = 0;
	if (line[0] == 'L')
		return(free_node(NULL, line, 1));
	while (line[name] != ' ' && line[name] != '\0')
		name++;
	if (line[name] == '\0')
		return (free_node(NULL, line, 1));
	if (!(node = (t_node *)malloc(sizeof(t_node))))
		return (free_node(NULL, line, 1));
	node->name = ft_strsub(line, 0, name);
	if (!get_coord(line + name, node))
		return (free_node(node, line, 3));
	node->next = *prev;
	*prev = node;
	*count += 1;
	return (node);
}

static int		get_start_end(char **line, t_lem_in *lem_in, int count)
{
	if (line[0][1] == '#')
	{
		if (lem_in->flags & 3)
		{
			free(*line);
			return (1);
		}
		if (ft_strcmp(*line, "##start") == 0 && !(lem_in->flags & 1)
				&& (lem_in->flags |= 1))
			lem_in->start = count;
		else if (ft_strcmp(*line, "##end") == 0 && !(lem_in->flags & 2)
				&& (lem_in->flags |= 2))
			lem_in->end = count;
		else
		{
			free(*line);
			return (1);
		}
	}
	free(*line);
	get_line(line);
	return (0);
}

t_lem_in    	*get_nodes(void)
{
    char        *line;
    t_lem_in    *lem_in;
	t_node		*node;
	t_node		*prev;
	size_t		count;

	if (!(lem_in = init()))
		return (NULL);
	count = 0;
	prev = NULL;
    while (get_line(&line))
    {
        if (ft_strchr(line, '-'))
            break ;
		if (line[0] == '#')
			if (get_start_end(&line, lem_in, count))
				return ((t_lem_in *)free_all(lem_in, prev, 19));
		if (!(node = get_node(line, &prev, &count)))
				return ((t_lem_in *)free_all(lem_in, prev, 19));
		free(line);
		line = NULL;
	}
	if (check_node_er(lem_in, line, count, node))
		return (NULL);
	return (lem_in);
}
