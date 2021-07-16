#include <stdio.h>

typedef struct s_TreeNode
{
	int data;
	struct s_TreeNode *left, *right;
}				t_TreeNode;

#define SIZE 100
int top = -1;
t_TreeNode *stack[SIZE];


void push (t_TreeNode *p)
{
	if(top < SIZE - 1)
		stack[++top] = p;
}

t_TreeNode *pop()
{
	t_TreeNode *p = NULL;
	if(top >= 0)
		p = stack[top--];
	return p;
}

void inorder_iter(t_TreeNode *root)
{
	while(1)
	{
		for(; root; root = root->left)
			push(root);
		root = pop();
		if(!root) break;
		printf("[%d] ", root->data);
		root = root->right;
	}
}


t_TreeNode n1 = {1, NULL, NULL};
t_TreeNode n2 = {4, &n1, NULL}; 
t_TreeNode n3 = {16, NULL, NULL};
t_TreeNode n4 = {25, NULL, NULL};
t_TreeNode n5 = {20, &n3, &n4};
t_TreeNode n6 = {15, &n2, &n5};
t_TreeNode *root = &n6;

int main()
{
	printf("중위순회 = ");
	inorder_iter(root);
	printf("\n");
	return 0;
}
