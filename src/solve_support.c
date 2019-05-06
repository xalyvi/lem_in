#include "lem_in.h"

int	not_in(size_t k, t_node *n)
{
    while (n)
    {
        if (k == n->key)
            return (0);
        n = n->next;
    }
    return (1);
}