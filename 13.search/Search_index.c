#include <stdio.h>

#define INDEX_SIZE 256
typedef struct
{
	int key;
	int index;
}	itable;

itable index_list[INDEX_SIZE] = {{3, 0}, {22, 3}, {67, 6}};

int list[INDEX_SIZE] = {3, 9, 15, 22, 31, 55, 67, 88, 91};

int seq_search(int key, int low, int high)
{
	int i;

	for (i = low; i <= high; i++)
		if(list[i] == key)
			return i;
	return -1;
}

int search_index(int key, int n)
{
	int i, low, high;

	if(key < list[0] || key > list[n - 1])
		return -1;
	for (i = 0; i < 3; ++i)
	{
		if (index_list[i].key <= key &&
			index_list[i + 1].key > key)
		break;
			printf("index_list[%d].%d\n" , i, index_list[i].key);
	}	
	if(i == 3)
	{
		low = index_list[i - 1].index;
		high = n;
	}
	else
	{
		low = index_list[i].index;
		high = index_list[i + 1].index;
	}
	return seq_search(key, low, high);
}

int main()
{
	int key = 67;
	int n = 9;	

	int re = search_index(key, n);
	
	if(re == -1)
		printf("not found\n");
	else
		printf("list[%d] == %d\n", re, list[re]);
}
	
