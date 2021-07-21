#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 10

typedef int element;

typedef struct
{
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}		t_QueueType;


#define MAX_VERTICES 50

typedef struct s_GraphType
{
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
}	t_GraphType;

int visited[MAX_VERTICES];

void graph_init(t_GraphType *g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; ++r)
		for(c = 0; c < MAX_VERTICES; ++c)
			g->adj_mat[r][c] = 0;
}

void insert_vertex(t_GraphType *g, int v)
{
	if(((g->n) + 1) > MAX_VERTICES)
	{
		fprintf(stderr, "그래프 : 정점의 개수 초과");
		return;
	}
	g->n++;
}

void print_adj_mat(t_GraphType *g)
{
	for(int i = 0; i < g->n; i++)
	{
		for(int j = 0; j < g->n; j++)
			printf("%d ", g->adj_mat[i][j]);
		printf("\n");
	}
	printf("\n");
}

void insert_edge(t_GraphType *g, int start, int end)
{
	if(start >= g->n || end >= g->n)
	{
		fprintf(stderr, "그래프, 정점 번호 오류");
		return ;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

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

void bfs_mat(t_GraphType *g, int v)
{
	int w;
	t_QueueType q;

	queue_init(&q);
	visited[v] = TRUE;
	printf("%d 방문 -> ", v);
	enqueue(&q, v);

	while(!is_empty(&q))
	{
		v = dequeue(&q);
		for (w = 0; w < g->n; w++)
			if (g->adj_mat[v][w] && !visited[w])
			{
				visited[w] = TRUE;
				printf("%d 방문 -> ", w);
				enqueue(&q, w);
			}
	}
}

int main(void)
{
	t_GraphType *g;
	g = (t_GraphType *)malloc(sizeof(t_GraphType));
	graph_init(g);

	for(int i = 0; i < 6; i++)
		insert_vertex(g, i);

	insert_edge(g, 0, 2);
	insert_edge(g, 2, 1);
	insert_edge(g, 2, 3);
	insert_edge(g, 0, 4);
	insert_edge(g, 4, 5);
	insert_edge(g, 1, 5);

	printf("init_mat\n");
	print_adj_mat(g);

	printf("너비 우선 탐색\n");
	bfs_mat(g, 0);
	printf("\n");
	free(g);
	return 0;
}
