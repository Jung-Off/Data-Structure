#include <stdio.h>

int list[5] = {9, 5, 8, 3, 7};

int seq_search(int key, int low, int high)
{
	int i;

	for (i = low; i <= high; i++)
		if(list[i] == key)
			return i;
	return -1;
}
	

int main()
{
	int key = 2;
	int low = 0;
	int high = 5;
	
	int re = seq_search(key, low, high);
	
	if(re == -1)
		printf("not found\n");
	else
		printf("list[%d] == %d\n", re, list[re]);
}
	
