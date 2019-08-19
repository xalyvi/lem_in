/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 21:12:08 by srolland          #+#    #+#             */
/*   Updated: 2019/08/19 21:12:10 by srolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	swap(t_paths **a, t_paths **b)
{
	t_paths *t;

	t = *a;
	*a = *b;
	*b = t;
}

static int	partition(t_paths **arr, int low, int high)
{
	int pivot;
	int i;
	int	j;

	pivot = (int)arr[high]->length;
	i = (low - 1);
	j = low;
	while (j <= high - 1)
	{
		if ((int)(arr[j]->length) <= pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
		j++;
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

static void	quicksort(t_paths **arr, int low, int high)
{
	int pi;

	if (low < high)
	{
		pi = partition(arr, low, high);
		quicksort(arr, low, pi - 1);
		quicksort(arr, pi + 1, high);
	}
}

static void	create_path(t_paths *paths, t_links *links, size_t key)
{
	t_node *node;
	t_node *prev;

	prev = NULL;
	while (1)
	{
		paths->length++;
		node = (t_node *)malloc(sizeof(t_node));
		node->ant = 0;
		node->key = key;
		node->next = prev;
		if (links[key].level == INT_MAX)
		{
			paths->path = node;
			break ;
		}
		prev = node;
		key = links[key].output->key;
	}
}

t_paths		**make_paths(t_links *links, size_t start)
{
	t_paths	**paths;
	size_t	i;
	t_node	*node;

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
	quicksort(paths, 0, (int)links[start].o - 1);
	return (paths);
}
