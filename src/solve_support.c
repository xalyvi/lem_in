#include "lem_in.h"

void    fill_array(int distance[], int count)
{
    while (count > 0)
    {
        distance[count - 1] = -1;
        count--;
    }
}