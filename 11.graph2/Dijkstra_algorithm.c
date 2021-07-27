#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct s_GraphType
{
	int n;
	int weight[MAX_VERTICES][MAX_VERTICES];
}				t_GraphType;

int distance[MAX_VERTICES];
int found[MAX_VERTICES];

int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for(i = 0; i < n; i++)
		if(distance[i] < min && !found[i])
		{
			min = distance[i];
			minpos = i;
		}
	return minpos;
}
void print_status(t_GraphType *g)
{
	static int step = 1;
	printf("STEP %d : ", step++);
	printf("distance : ");
	for(int i = 0; i < g->n; i++)
		if(distance[i] == INF)
			printf(" * ");
		else
			printf("%2d ", distance[i]);
	printf("\n");
	printf(" found : ");
	for(int i = 0; i < g->n; i++)
		printf("%d ", found[i]);
	printf("\n\n");
}

void shortest_path(t_GraphType *g, int start)
{
	int i, u, w;
	for (i = 0; i < g->n; ++i)
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE;
	distance[start] = 0;
	for (i = 0; i < g->n-1; i++)
	{
		print_status(g);
		u = choose(distance, g->n, found);
		found[u] = TRUE;
		for (w = 0; w < g->n; ++w)
			if(!found[w])
				if (distance[u] + g->weight[u][w] < distance[w])
					distance[w] = distance[u] + g->weight[u][w];
	}
}

int main()
{	
	t_GraphType g = {8,
	{{ 0, 7, INF, 5, INF, 2, INF, INF},
	{ 7, 0, 6, INF, 2, INF, INF, 1},
	{ INF, 6, 0, 2, INF, INF, 2, 4}, 
	{ 5, INF, 2, 0, INF, 5, INF, INF},
	{ INF, 2, INF, INF, 0, 2, INF, 4},
	{ 2, INF, INF, 5, 2, 0, 4, INF},
	{INF, INF, 2, INF, INF, 4, 0, 4},
	{INF, 1, 8, INF, 4, INF, 4, 0}}
	};
/*
	t_GraphType g = {7,
	{{ 0, 7, INF, INF, 3, 10, INF},
	{ 7, 0, 4, 10, 2, 6, INF},
	{ INF, 4, 0, 2, INF, INF, INF},
	{ INF, 10, 2, 0, 11, 9, 4},
	{ 3, 2, INF, 11, 0, INF, 5},
	{10, 6, INF, 9, INF, 0, INF},
	{INF, INF, INF, 4, 5, INF, 0}}
	};
*/
	shortest_path(&g, 0);
	return 0;
}
