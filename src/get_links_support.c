#include "lem_in.h"

t_links    *init_links(size_t count)
{
    t_links *links;
    size_t  i;

    links = (t_links *)malloc(sizeof(t_links) * count);
    i = 0;
    while (i < count)
    {
        links[i].flags = 0;
        links[i].visited = 0;
        links[i].link = NULL;
        i++;
    }
    return (links);
}