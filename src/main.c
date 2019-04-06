#include "lem_in.h"

int main(void)
{
    char		*line;
	int			ants;
	t_lem_in	*lem_in;

	ants = 0;
	get_line(&line);
	if (line[0] == '0' && line[1] != '\0')
		return (0);
	ants = ft_atoi(line);
	free(line);
	if (ants == 0)
		return (0);
	lem_in = get_nodes();
	//get_links(lem_in);
}