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

int main()
{
	t_GraphType *g;
	g = (t_GraphType *)malloc(sizeof(t_GraphType));
	init(g);

	for(int i = 0; i < 4; i++)
		insert_vertex(g, i);

//	print_adj_lsit(g);

	insert_edge(g, 0, 1);
	print_adj_list(g);

	insert_edge(g, 1, 0);
	print_adj_list(g);

	insert_edge(g, 0, 2);
	print_adj_list(g);

	insert_edge(g, 2, 0);
	print_adj_list(g);

	insert_edge(g, 0, 3);
	print_adj_list(g);

	insert_edge(g, 3, 0);
	print_adj_list(g);

	insert_edge(g, 1, 2);
	print_adj_list(g);

	insert_edge(g, 2, 1);
	print_adj_list(g);

	insert_edge(g, 2, 3);
	print_adj_list(g);

	insert_edge(g, 3, 2);
	print_adj_list(g);

	return 0;
}
