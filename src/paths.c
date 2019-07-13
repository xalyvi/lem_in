#include "lem_in.h"

static void	swap(t_paths** a, t_paths** b) 
{ 
    t_paths *t = *a; 
    *a = *b; 
    *b = t; 
} 

static int	partition (t_paths **arr, int low, int high) 
{ 
    int pivot = (int)arr[high]->length;
    int i = (low - 1);
  
    for (int j = low; j <= high- 1; j++) 
    { 
        if ((int)(arr[j]->length) <= pivot) 
        { 
            i++;
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
}
  
static void	quickSort(t_paths **arr, int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition(arr, low, high); 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
}

static void	create_path(t_paths *paths, t_links *links, size_t key)
{
	t_node	*node;
	t_node	*prev;

	while (1)
	{
		paths->length++;
		node = (t_node *)malloc(sizeof(t_node));
		node->ant = 0;
		node->key = key;
		node->next = NULL;
		if (paths->path == NULL)
			paths->path = node;
		else
			prev->next = node;
		if (links[key].level == INT_MAX)
			break ;
		prev = node;
		key = links[key].output->key;
	}
}

t_paths 	**make_paths(t_links *links, size_t start)
{
	t_paths **paths;
	size_t	i;
	t_node  *node;

	node = links[start].output;
	if (!(paths = (t_paths **)malloc(sizeof(t_paths *) * links[start].o)))
		return (NULL);
	i = 0;
	while (i < links[start].o)
	{
		paths[i] = (t_paths *)malloc(sizeof(t_paths));
		paths[i]->length = 0;
		paths[i]->path = NULL;
		create_path(paths[i], links, node->key);
		i++;
		node = node->next;
	}
	quickSort(paths, 0, (int)links[start].o - 1);
	return (paths);
}