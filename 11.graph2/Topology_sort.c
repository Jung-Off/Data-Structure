#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

typedef struct s_GraphNode
{
	int vertex;
	struct s_GrapNode *link;
}				t_GraphNode;

typedef struct s_GraphType
{
	int n;
	t_GraphNode *adj_list[MAX_VERTICES];
}				t_GraphType;

void graph_init(t_GraphType *g)
{
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}

void insert_vertex(t_GraphType *g, int v)
{
	if(((g->n) + 1) > MAX_VERTICES)
	{
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

void insert_edge(t_GraphType *g, int u, int v)
{
	t_GraphNode *node;
	if(u >= g->n || v >= g->n)
	{
		fprintf(stderr, "그래프 : 정점번호 오류");
		return ;
	}
	node = (t_GraphNode *)malloc(sizeof(t_GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}


//////////////////////////////////

#define MAX_STACK_SIZE 100
typedef int element;
typedef struct
{
	element stack[MAX_STACK_SIZE];
	int top;
}		t_StackType;

void init(t_StackType *s)
{
	s->top = -1;
}

int is_empty(t_StackType *s)
{
	return(s->top == -1);
}

int is_full(t_StackType *s)
{
	return(s->top == (MAX_STACK_SIZE -1));
}

void push(t_StackType *s, element item)
{
	if(is_full(s))
	{
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}

element pop(t_StackType *s)
{
	if(is_empty(s))
	{
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->stack[(s->top)--];
}

int topo_sort(t_GraphType *g)
{
	int i;
	t_StackType s;
	t_GraphNode *node;

	int *in_degree = (int *)malloc(g->n * sizeof(int));
	for(i = 0; i < g->n; i++)
		in_degree[i] = 0;
	for(i = 0; i < g->n; i++)
	{
		t_GraphNode *node = g->adj_list[i];
		while(node != NULL)
		{
			in_degree[node->vertex]++;
			node = node->link;
		}
	}
	
	init(&s);
	for(i = 0; i < g->n; i++)
		if(in_degree[i] == 0) push(&s, i);

	while(!is_empty(&s))
	{
		int w;
		w = pop(&s);
		printf("정점 %d -> ", w);
		node = g->adj_list[w];
		while(node != NULL)
		{
			int u = node->vertex;
			in_degree[u]--;
			if(in_degree[u] == 0)
				push(&s, u);
			node = node->link;
		}
	}
	free(in_degree);
	printf("\n");
	return(i == g->n);
}

int main()
{
	t_GraphType g;

	graph_init(&g);
	insert_vertex(&g, 0);	
	insert_vertex(&g, 1);	
	insert_vertex(&g, 2);	
	insert_vertex(&g, 3);	
	insert_vertex(&g, 4);	
	insert_vertex(&g, 5);	

	insert_edge(&g, 0, 2);
	insert_edge(&g, 0, 3);
	insert_edge(&g, 1, 3);
	insert_edge(&g, 1, 4);
	insert_edge(&g, 2, 3);
	insert_edge(&g, 2, 5);
	insert_edge(&g, 3, 5);
	insert_edge(&g, 4, 5);

	topo_sort(&g);

	return 0;

}
