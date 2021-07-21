#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50

typedef struct s_GraphNode
{
	int vertex;
	struct s_GraphNode *link;
}				t_GraphNode;

typedef struct s_GraphType
{
	int n;
	t_GraphNode *adj_list[MAX_VERTICES];
}			t_GraphType;

//queue

#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 10

typedef int element;

typedef struct
{
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}	t_QueueType;

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

//

void init(t_GraphType *g)
{
	int v;
	g->n = 0;
	for(v = 0; v < MAX_VERTICES; ++v)
		g->adj_list[v] = NULL;
}


void insert_vertex(t_GraphType *g, int v)
{
	if ((g->n) + 1 > MAX_VERTICES)
	{
		fprintf(stderr, "그래프 : 정점의 개수 초과");
		return ;
	}
	g->n++;
}

void insert_edge(t_GraphType *g, int u, int v)
{
	t_GraphNode *node;
	if (u >= g->n || v >= g->n)
	{
		fprintf(stderr, "그래프 : 정점 번호 오류");
		return ;
	}
	node = (t_GraphNode*)malloc(sizeof(t_GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

void print_adj_list(t_GraphType *g)
{
	for(int i = 0; i < g->n; ++i)
	{
		t_GraphNode *p = g->adj_list[i];
		printf("정점 %d의 인접 리스트 " , i);
		while(p != NULL)
		{
			printf("-> %d ", p->vertex);
			p = p->link;
		}
		printf("\n");
	}
	printf("\n");
}

int visited[MAX_VERTICES];

void bfs_list(t_GraphType *g, int v)
{
	t_GraphNode *w;
	t_QueueType q;

	queue_init(&q);
	visited[v] = TRUE;
	printf("%d 방문 -> ", v);
	enqueue(&q, v);
	while (!is_empty(&q))
	{
		v = dequeue(&q);
		for(w = g->adj_list[v]; w; w = w->link)
			if (!visited[w->vertex])
			{
				visited[w->vertex] = TRUE;
				printf("%d 방문 -> ", w->vertex);
				enqueue(&q, w->vertex);
			}
	}
}

#define VERTEX_SIZE 6

int main()
{
	t_GraphType *g;
	g = (t_GraphType *)malloc(sizeof(t_GraphType));
	init(g);

	for(int i = 0; i < VERTEX_SIZE; i++)
		insert_vertex(g, i);

	
	insert_edge(g, 0, 4);
	insert_edge(g, 0, 2);
	insert_edge(g, 1, 5);
	insert_edge(g, 1, 2);
	insert_edge(g, 2, 3);
	insert_edge(g, 2, 1);
	insert_edge(g, 2, 0);
	insert_edge(g, 3, 2);
	insert_edge(g, 4, 5);
	insert_edge(g, 4, 0);
	insert_edge(g, 5, 4);
	insert_edge(g, 5, 1);

	print_adj_list(g);	
	
	bfs_list(g, 0);
	free(g);
	return 0;
}
