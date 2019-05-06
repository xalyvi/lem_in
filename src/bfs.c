#include "lem_in.h"

static void		to_path(t_node **path, size_t start)
{
    t_node *tmp;
    t_node  *n;

    tmp = *path;
    n = (t_node *)malloc(sizeof(t_node));
    n->key = start;
    n->next = NULL;
    if (!tmp)
    {
		*path = n;
		return ;
    }
    while (tmp && tmp->next)
	tmp = tmp->next;
    tmp->next = n;
}

static int		shuffle_queue(t_lem_in *lem_in, t_node *tmp, t_queue *q, t_node *path)
{
	while (tmp)
	{
		if (tmp->key == lem_in->end)
		{
			to_path(&path, tmp->key);
			return (1);
		}
		if (!lem_in->links[tmp->key].visited)
		{
			lem_in->links[tmp->key].visited = 1;
			enqueue(q, tmp->key);
			while (not_in(peek(q), tmp))
				enqueue(q, dequeue(q));
		}
		tmp = tmp->next;
	}
	return (0);
}

static int		valid_path(t_node *path, size_t start, size_t end)
{
    if (path->key != start)
        return (0);
    while (path && path->next)
        path = path->next;
    if (path->key != end)
        return (0);
    return (1);
}

static t_node	*ret(t_queue *q, t_node *path)
{
    while (!is_empty(q))
        dequeue(q);
    free(q);
    return(path);
}

t_node *bfs(t_lem_in *lem_in, size_t start)
{
	t_node *path;
    t_node *tmp;
    t_node *tmp2;
	t_queue *q;

    path = NULL;
    start = lem_in->start;
    lem_in->links[start].visited = 1;
    q = create_queue();
    enqueue(q, start);
    while (!is_empty(q))
    {
        start = dequeue(q);
        to_path(&path, start);
        tmp = path;
        while (tmp)
            tmp = tmp->next;
        tmp2 = lem_in->links[start].link;
        if (shuffle_queue(lem_in, tmp2, q, path))
            return (ret(q, path));
    }
    if (!valid_path(path, lem_in->start, lem_in->end))
    	return (NULL);
    free(q);
    return (path);
}