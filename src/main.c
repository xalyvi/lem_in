#include "lem_in.h"
#include <stdio.h>

// static void	print_shit(t_lem_in *lem_in, t_node *path)
// {
// 	size_t i;
// 	t_node	*q;

// 	i = 0;
// 	printf("Start: %s; End: %s;\n", lem_in->rooms[lem_in->start]->name, lem_in->rooms[lem_in->end]->name);
// 	while (i < lem_in->count)
// 	{
// 		printf("Name: %s;", lem_in->rooms[i]->name);
// 		if (lem_in->links[i].link)
// 		{
// 			printf(" Links:");
// 			q = lem_in->links[i].link;
// 			while (q)
// 			{
// 				printf(" %s", lem_in->rooms[q->key]->name);
// 				q = q->next;
// 			}
// 		}
// 		printf("\n");
// 		i++;
// 	}
// 	printf("\nPath:\n");
// 	while (path)
// 	{
// 		printf("%s", lem_in->rooms[path->key]->name);
// 		if (path->next)
// 			printf("->");
// 		path = path->next;
// 	}
// 	printf("\n");
// }

// static void	lem_names(t_lem_in *lem_in)
// {
// 	size_t	i;

// 	lem_in->names = (char **)malloc(sizeof(char *) * lem_in->count);
// 	i = 0;
// 	while (i < lem_in->count)
// 	{
// 		lem_in->names[i] = ft_strdup(lem_in->rooms[i]->name);
// 		i++;
// 	}
// }

int 		main(void)
{
    char		*line;
	int			ants;
	t_lem_in	*lem_in;
	t_node		*path;

	ants = 0;
	line = NULL;
	get_line(&line);
	if (line == NULL || line[0] == '0')
		return (0);
	ants = ft_atoi(line);
	ft_putendl(line);
	free(line);
	if (!(lem_in = get_rooms()))
		return (0);
	lem_in->ants = ants;
	if (!get_links(lem_in))
		return (0);
	path = bfs(lem_in, 0);
	// print_shit(lem_in, path);
	write(1, "\n", 1);
	move_ants(lem_in, path);
	return (0);
}
