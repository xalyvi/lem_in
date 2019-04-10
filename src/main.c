#include "lem_in.h"

int 		main(void)
{
    char		*line;
	int			ants;
	t_lem_in	*lem_in;

	ants = 0;
	line = NULL;
	get_line(&line);
	if (line == NULL || line[0] == '0')
		return (0);
	ants = ft_atoi(line);
	free(line);
	if (!(lem_in = get_nodes()))
		return (0);
	lem_in->ants = ants;
	if (!get_links(lem_in))
		return (0);
	solve_lem_in(lem_in);
	return (0);
}
