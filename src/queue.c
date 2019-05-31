/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:42:53 by srolland          #+#    #+#             */
/*   Updated: 2019/05/30 16:42:54 by srolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_queue	*create_queue(void)
{
	t_queue	*q;

	if (!(q = (t_queue *)malloc(sizeof(t_queue))))
		return (NULL);
	q->front = NULL;
	q->rear = NULL;
	return (q);
}

void	enqueue(t_queue *q, int key)
{
	t_node	*n;

	if (!(n = (t_node *)malloc(sizeof(t_node))))
		return ;
	n->key = key;
	n->next = NULL;
	if (q->rear == NULL)
	{
		q->front = n;
		q->rear = n;
		return ;
	}
	q->rear->next = n;
	q->rear = n;
}

size_t	dequeue(t_queue *q)
{
	size_t	num;
	t_node	*tmp;

	if (q->front == NULL)
		return (0);
	tmp = q->front;
	num = q->front->key;
	q->front = q->front->next;
	free(tmp);
	tmp = NULL;
	if (q->front == NULL)
		q->rear = NULL;
	return (num);
}

size_t	peek(t_queue *q)
{
	if (q->front)
		return (q->front->key);
	return (0);
}

int		is_empty(t_queue *q)
{
	return (!q->front && !q->rear);
}
