#include "lem_in.h"

t_queue		*create_queue(void)
{
	t_queue	*q;

	if (!(q = (t_queue *)malloc(sizeof(t_queue))))
		return (NULL);
	q->front = NULL;
	q->rear = NULL;
	return (q);
}

static void	*q_new_node(int key)
{
	t_qnode *n;

	if (!(n = (t_qnode *)malloc(sizeof(t_qnode))))
		return (NULL);
	n->key = key;
	n->next = NULL;
	return (n);
}

void		add_qnode(t_queue *q, int key)
{
	t_qnode	*n;

	if (!(n = q_new_node(key)))
		return ;
	if (q->rear == NULL)
	{
		q->front = n;
		q->rear = n;
		return ;
	}
	q->rear->next = n;
	q->rear = n;
}

int			poll_qnode(t_queue *q)
{
	int		rt;
	t_qnode	*temp;

	if (q->front == NULL)
		return (-1);
	rt = q->rear->key;
	temp = q->rear;
	q->rear->next = NULL;
}

void		delete_qnode(t_queue *q)
{
	t_qnode	*n;

	if (q->front == NULL)
		return ;
	n = q->front;
	q->front = q->front->next;
	free(n);
	if (q->front == NULL)
		q->rear = NULL;
}