#include <stdio.h>

int list[10] = { 3, 9, 15, 22, 31, 55, 67, 88, 89, 91};

int interpol_search(int key, int n)
{
	int low, high, j;

	low = 0;
	high = n - 1;
	while ((list[high] >= key) && (key >list[low]))
	{
		j = ((float)(key - list[low]) / (list[high] - list[low]) * (high - low)) + low;
		printf("list[%d] = %d\n", j, list[j]);
		if (key > list[j]) low = j + 1;
		else if (key < list[j]) high = j - 1;
		else low = j;
	}
	if(list[low] == key) return(low);
	else return -1;
}

int main()
{
	int key = 89;

	int re = interpol_search(key, 10);
	printf("after_search\n");
	if(re == -1)
		printf("not found\n");
	else
		printf("list[%d] = %d\n", re, list[re]);
}
