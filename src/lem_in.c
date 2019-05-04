#include "lem_in.h"

void	solve_lem_in(t_lem_in *lem_in)
{
	t_queue	*q;
	int		distance[lem_in->count];

    q = create_queue();
    add_qnode(q, lem_in->start);
	distance[lem_in->start] = 0;
	fill_arrays(distance, lem_in->count);
}