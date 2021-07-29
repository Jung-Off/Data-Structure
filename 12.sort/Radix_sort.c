#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_QUEUE_SIZE 100
typedef int element;

typedef struct
{
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}		t_QueueType;



void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void queue_init(t_QueueType *q)
{
	q->front = q->rear = 0;
}

int is_empty(t_QueueType *q)
{
	return(q->front == q->rear);
}

int is_full(t_QueueType *q)
{
	return((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(t_QueueType *q, element item)
{
	if(is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

element dequeue(t_QueueType *q)
{
	if (is_empty(q))
		error("큐가 공백 상태 입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

#define BUCKETS 10
#define DIGITS 4

void radix_sort(int list[], int n)
{
	int i, b, d, factor = 1;
	t_QueueType queues[BUCKETS];

	for (b = 0; b < BUCKETS; b++)
		queue_init(&queues[b]);

	for(d = 0; d < DIGITS; d++)
	{
		for(i = 0; i < n; i++)
			enqueue(&queues[(list[i] /factor) % 10], list[i]);
		
		for(b = i = 0; b < BUCKETS; b++)
			while(!is_empty(&queues[b]))
				list[i++] = dequeue(&queues[b]);
		factor *= 10;
	}
}

#define SIZE 10

int main(void)
{
	int list[SIZE];
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++)
		list[i] = rand() % 100;

	printf("before_sort\n");
	for(int i = 0; i < SIZE; i++)
		printf("%d ", list[i]);
	printf("\n");

	radix_sort(list, SIZE);
	printf("after_sort\n");
	for (int i = 0; i < SIZE; i++)
		printf("%d ", list[i]);
	printf("\n");
	return 0;
}
