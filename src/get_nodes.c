#include "lem_in.h"
#include <stdio.h>
#include <unistd.h>

static t_lem_in	*init(void)
{
	t_lem_in	*lem_in;

	if (!(lem_in = (t_lem_in *)malloc(sizeof(t_lem_in))))
		return (NULL);
	lem_in->start = -1;
	lem_in->end = -1;
	return (lem_in);
}

static char		*get_coord(char *line, t_node *node)
{
	while (*line == ' ' && *line != '\0')
		line++;
	if (*line == '\0' || (*line == '0' && *line != ' '))
		return (NULL);
	node->x = ft_atoi(line);
	while (*line >= '0' && *line <= '9')
		line++;
	while (*line == ' ' && line != '\0')
		line++;
	if (*line == '\0' || (*line == '0' && *line != '\0'))
		return (NULL);
	node->y = ft_atoi(line);
	while (*line >= '0' && *line <= '9')
		line++;
	if (*line == '\0')
		return (line);
	return (NULL);
}

static t_node	*get_node(char *line, t_node *prev)
{
	t_node	*node;
	size_t	name;

	if (!(node = (t_node *)malloc(sizeof(t_node))))
		return (NULL);
	name = 0;
	while (line[name] != ' ' && line[name] != '\0')
		name++;
	if (line[name] == '\0')
	{
		free(node);
		return (NULL);
	}
	node->name = ft_strsub(line, 0, name);
	if (!get_coord(line + name, node))
	{
		free(node);
		return (NULL);
	}
	node->next = prev;
	return (node);
}

static int		get_start_end(char *line, t_lem_in *lem_in, int count)
{
	if (ft_strcmp(line, "##start") == 0)
		lem_in->start = count + 1;
	else if (ft_strcmp(line, "##end") == 0)
		lem_in->end = count + 1;
	else
		return (1);
	return (0);
}

t_lem_in    	*get_nodes(void)
{
    char        *line;
    t_lem_in    *lem_in;
	t_node		*node;
	t_node		*prev;
	int			count;

	if (!(lem_in = init()))
		return (NULL);
	count = 0;
	prev = NULL;
    while (get_line(&line))
    {
        if (ft_strchr(line, '-'))
            break ;
		if ((line[0] == '#' && line[1] == '#') || (line[0] != '#' && line[0] != '#'))
		{
			if (line[0] == '#' && line[1] == '#')
			{
				if (get_start_end(line, lem_in, count))
					return (NULL);
				free(line);
				get_line(&line);
			}
			if (!(node = get_node(line, prev)))
				return (NULL);
			else
			{
				count++;
				prev = node;
			}
		}
	}
	while (count > 0)
	{
		printf("%s %d %d", node->name, node->x, node->y);
		if (count == lem_in->start)
			printf(" start\n");
		else if (count == lem_in->end)
			printf(" end\n");
		else
			printf("\n");
		node = node->next;
		count--;
	}
	return (NULL);
}