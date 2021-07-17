#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct s_TreeNode
{
	element key;
	struct s_TreeNode *left;
	struct s_TreeNode *right;
}				t_TreeNode;

t_TreeNode *search(t_TreeNode *node, int key)
{
	if(node == NULL)
		return NULL;
	if(key == node ->key)
		return node;
	else if (key < node ->key)
		return search(node->left, key);
	else
		return search(node->right, key);
}

t_TreeNode *new_node(int item)
{
	t_TreeNode *temp = (t_TreeNode *)malloc(sizeof(t_TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

t_TreeNode *insert_node(t_TreeNode *node, int key)
{
	if(node == NULL)
		return new_node(key);
	if(key < node->key)
		node->left = insert_node(node->left, key);
	else if(key > node->key)
		node->right = insert_node(node->right, key);
	return node;
}

//delete_node

t_TreeNode *min_value_node(t_TreeNode *node)
{
	t_TreeNode *current = node;

	while(current->left != NULL)
		current = current -> left;

	return current;
}


void inorder(t_TreeNode * root)
{
	if(root)
	{
		inorder(root->left);
		printf("[%d] ", root->key);
		inorder(root->right);
	}
}

t_TreeNode *delete_node(t_TreeNode *root, int key)
{
	if(root == NULL)
		return root;

	if(key < root->key)
		root->left = delete_node(root->left, key);
	else if(key > root->key)
		root->right = delete_node(root->right, key);
	else
	{
		if(root->left == NULL)
		{
			t_TreeNode *temp = root->right;
			free(root);
			return temp;
		}
		else if(root->right == NULL)
		{
			t_TreeNode *temp = root->left;
			free(root);
			return temp;
		}
		
		t_TreeNode *temp = min_value_node(root->right);

		root->key = temp->key;
		root->right = delete_node(root->right, temp->key);
	}
	return root;
}

#define NUM 30

/*
		30
	20		40
10				50
					60
*/

int main(void)
{
	t_TreeNode *root = NULL;

	root = insert_node(root, 30);
	root = insert_node(root, 20);
	root = insert_node(root, 10);
	root = insert_node(root, 40);
	root = insert_node(root, 50);
	root = insert_node(root, 60);

	printf("이진 탐색 트리 중위 순회 결과 \n");
	
	//root = delete_node(root, 30);
	inorder(root);
	printf("\n\n");

	if(search(root, NUM) != NULL)
		printf("이진 탐색 트리에서 %d을 발견함 \n", NUM);
	else
		printf("이진 탐색 트리에서 %d을 발견 못함\n", NUM);	
	return 0;
}
