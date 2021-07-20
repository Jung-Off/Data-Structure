#include <stdio.h>

typedef struct s_TreeNode
{
	int data;
	struct s_TreeNode *left;
	struct s_TreeNode *right;
}				t_TreeNode;

/*
		15
	4			20
1			16		25
*/

t_TreeNode	g_n1 = {1, NULL, NULL};
t_TreeNode	g_n2 = {4, &g_n1, NULL};
t_TreeNode	g_n3 = {16, NULL, NULL};
t_TreeNode	g_n4 = {25, NULL, NULL};
t_TreeNode	g_n5 = {20, &g_n3, &g_n4};
t_TreeNode	g_n6 = {15, &g_n2, &g_n5};
t_TreeNode	*g_root = &g_n6;

t_TreeNode	G_n1 = {1, NULL, NULL};
t_TreeNode	G_n2 = {4, &G_n1, NULL};
t_TreeNode	G_n3 = {16, NULL, NULL};
t_TreeNode	G_n4 = {25, NULL, NULL};
t_TreeNode	G_n5 = {20, &G_n3, &G_n4};
t_TreeNode	G_n6 = {15, &G_n2, &G_n5};
t_TreeNode	*G_root = &G_n6;


/*
	3
2		1
*/

t_TreeNode n4 = {4, NULL, NULL};
t_TreeNode n2 = {2, &n4, NULL};
t_TreeNode n1 = {1, NULL, NULL};
t_TreeNode n3 = {3, &n2, &n1};
t_TreeNode *root = &n3;

#ifndef max
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#endif

//노드의 갯수 구하기
int get_node_count(t_TreeNode *root)
{
	int count = 0;

	if(root == NULL)
		return 0;	
	else
		count = 1 + get_node_count(root->left) + get_node_count(root->right);

	return count;
}

//단말 노드 갯수 구하기
int get_leaf_count(t_TreeNode *root)
{
	int count = 0;

	if(root != NULL)
	{
		if(root->left == NULL && root->right == NULL)
			return (1);
		else
			count = get_leaf_count(root->left) + get_leaf_count(root->right);
	}
	return (count);
}
//높이 구하기
int get_height(t_TreeNode *root)
{
	int count = 0;

	if(root == NULL)
		return (0); 
	else
		count = 1 + max(get_height(root->left), get_height(root->right));

	return (count);
} 

//비단말 노드의 갯수를 계산하는 함수

int get_nonleaf_count(t_TreeNode *root)
{
	int count = 0;

	if (root != NULL)
	{
		if(root->left == NULL && root->right == NULL)
			return(0);
		else
			count = 1 + get_nonleaf_count(root->left) + get_nonleaf_count(root->right);
	}
	return (count);
} 

//두개의 트리가 같은 구조를 가지고 있고 대응되는 노드들이 같은 데이터를 가지고 있는지
// 검사 하는 함수


int equal_1(t_TreeNode *t1, t_TreeNode *t2)
{
	int count = 0;

	if(t1 != NULL && t2 != NULL)
	{
		if(t1->data != t2->data)
			return(1);
		else
			count = equal_1(t1->left, t2->left) + equal_1(t1->right, t2->right); 
	}
	if(count >= 1)
		count = 1;	
	return(count);
}

int equal_2(t_TreeNode *t1, t_TreeNode *t2)
{
	int diff_count = 0;

	if(diff_count == 0)
	{
		if(t1 !=NULL && t2 != NULL)
		{
			if(t1->data != t2->data)
				return (1);
			else
				diff_count = equal_2(t1->left, t2->left) | equal_2(t1->right, t2->right);
		}
	}
	return (diff_count);
}

char *print_TRUE(int a)
{
	if(a == 0)
		return("equal\n");
	else
		return("different\n");
}

int main()
{
	printf("6 ==  node_count : %d\n", get_node_count(g_root));
	printf("3 ==  node_count : %d\n", get_node_count(root));	
	
	printf("3 == leaf_count : %d\n", get_leaf_count(g_root));
	printf("2 == leaf_count : %d\n", get_leaf_count(root));
	
	printf("3 == height : %d\n", get_height(g_root));
	printf("2 == height : %d\n", get_height(root));
	
	printf("3 == nonleaf : %d\n", get_nonleaf_count(g_root));
	printf("1 == nonleaf : %d\n", get_nonleaf_count(root));

	printf("ARE they equal ? : %s" , print_TRUE(equal_1(g_root, G_root)));
	printf("ARE they equal ? : %s" , print_TRUE(equal_2(g_root, G_root)));
}
