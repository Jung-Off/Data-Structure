#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
typedef struct s_GraphType
{
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
}				t_GraphType;

void init(t_GraphType *g)
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

int main()
{
	t_GraphType *g;
	g = (t_GraphType *)malloc(sizeof(t_GraphType));
	init(g);

	for(int i = 0; i < 4; i++)
		insert_vertex(g, i); //정점을 4개로 하고 싶다 0, 1, 2, 3

	printf("first\n");
	print_adj_mat(g);

	printf("0<-->1\n");
	insert_edge(g, 0, 1);
	print_adj_mat(g);

	printf("0<-->2\n");
	insert_edge(g, 0, 2);
	print_adj_mat(g);

	printf("0<-->3\n");
	insert_edge(g, 0, 3);
	print_adj_mat(g);

	printf("1<-->2\n");
	insert_edge(g, 1, 2);
	print_adj_mat(g);

	printf("2<-->3\n");
	insert_edge(g, 2, 3);
	print_adj_mat(g);

	free(g);
}
