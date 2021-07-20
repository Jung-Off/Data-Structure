#include <stdio.h>

typedef struct s_TreeNode
{
	int data;
	struct s_TreeNode *left;
	struct s_TreeNode *right;
}				t_TreeNode;

t_TreeNode	g_n1 = {1, NULL, NULL};
t_TreeNode	g_n2 = {4, &g_n1, NULL};
t_TreeNode	g_n3 = {16, NULL, NULL};
t_TreeNode	g_n4 = {25, NULL, NULL};
t_TreeNode	g_n5 = {20, &g_n3, &g_n4};
t_TreeNode	g_n6 = {15, &g_n2, &g_n5};
t_TreeNode	*g_root = &g_n6;

t_TreeNode n2 = {2, NULL, NULL};
t_TreeNode n1 = {1, NULL, NULL};
t_TreeNode n3 = {3, &n2, &n1};
t_TreeNode *root = &n3;

//get_node_count

int get_node_count_my(t_TreeNode *root)
{
	if(root == NULL)
		return (0);
	else
		return (1 + get_node_count_my(root->left) + get_node_count_my(root->right));
}

int get_node_count(t_TreeNode *root)
{
	int count = 0;
	
	if(root != NULL)
		count = 1 + get_node_count(root->left) + get_node_count(root->right);

	return (count);
}

//get_leaf_count

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

/*
int get_leaf_count(t_TreeNode *root)
{
	if(root->left == NULL && root->right == NULL)
		return (1);
	else
		return(get_leaf_count(root->left) + get_leaf_count(root->right));
}
*/

#ifndef max

#define max(a,b)  (((a) > (b)) ? (a) : (b))

#endif

int get_height(t_TreeNode *root)
{
	int count = 0;

	if(root != NULL)
			count = 1 + max(get_height(root->left), get_height(root->right));
	return (count);
}

int main()
{
	printf("6 ==  node_count : %d\n", get_node_count_my(g_root));
	printf("3 ==  node_count : %d\n", get_node_count_my(root));	
	printf("3 == leaf_count : %d\n", get_leaf_count(g_root));
	printf("2 == leaf_count : %d\n", get_leaf_count(root));
	printf("3 == height : %d\n", get_height(g_root));
	printf("2 == height : %d\n", get_height(root));
}
