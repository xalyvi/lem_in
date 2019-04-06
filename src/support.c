#include "lem_in.h"

void    free_all(t_lem_in *lem_in, int ap)
{
	size_t i;

	i = -1;
	if (ap)
		while ((lem_in->nodes)[++i] != 0)
			free(lem_in->nodes[i]->list);
	free(lem_in->nodes);
	free(lem_in);
}