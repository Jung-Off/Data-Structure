#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10

int list[MAX_SIZE];
int n;

void inc_insertion_sort(int list[], int first, int last, int gap)
{
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap)
	{
		key = list[i];
		for (j = i - gap; j >= first && key < list[j]; j = j - gap)
			list[j + gap] = list[j];
		list[j + gap] = key;
	}
}

void shell_sort(int list[], int n)
{
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2)
	{
		if ((gap % 2) == 0)
			gap++;
		for(i = 0; i < gap; i++)
			inc_insertion_sort(list, i , n - 1, gap);
	}
}

int main()
{
	int i;
	n = MAX_SIZE;
	srand(time(NULL));
	for(i = 0; i < n; i++)
		list[i] = rand() % 100;
	
	printf("before_sort\n");
	for(i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
	
	printf("after_sort\n");
	shell_sort(list, n);
	for(i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
	return 0;
}
