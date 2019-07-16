#include "lem_in.h"

static void delete_others(t_links *links, size_t key, t_node *save)
{
    t_node  *node;
    t_node  *prev;

    prev = NULL;
    node = links[key].output;
    while (node)
    {
        if (node != save)
        {
            if (!prev)
                links[key].output = node->next;
            else
                prev->next = node->next;
            free(node);
            if (!prev)
                node = links[key].output;
            else
                node = prev->next;
            links[key].o--;
        }
        else
        {
            prev = node;
            node = node->next;
        }
    }
}

void    iterate_output(t_links *links, size_t start)
{
    t_node  *node;
    t_node  *temp;
    size_t  key;
    size_t  len;
    size_t  cur;

    if (links[start].level == 0)
        return ;
    if (links[start].o > 1)
    {
        len = INT_MAX;
        temp = links[start].output;
        while (temp)
        {
            cur = 1;
            key = temp->key;
            while (links[key].level != INT_MAX)
            {
                key = links[key].output->key;
                cur++;
            }
            if (cur < len)
            {
                len = cur;
                node = temp;
            }
            temp = temp->next;
        }
        delete_others(links, start, node);
    }
    node = links[start].input;
    while (node)
    {
        iterate_output(links, node->key);
        node = node->next;
    }
}