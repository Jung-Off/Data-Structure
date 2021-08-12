#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct s_AVLNode
{
	int key;
	struct s_AVLNode *left;
	struct s_AVLNode *right;
}				t_AVLNode;

int get_height(t_AVLNode *node)
{
	int height = 0;
	if (node != NULL)
		height = 1 + MAX(get_height(node->left),get_height(node->right));
	return height;
}

int get_balance(t_AVLNode *node)
{
	if(node == NULL) return 0;

	return get_height(node->left) - get_height(node->right);
}

t_AVLNode *create_node(int key)
{
	t_AVLNode *node = (t_AVLNode*)malloc(sizeof(t_AVLNode));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_AVLNode *rotate_right(t_AVLNode *parent)
{
	t_AVLNode *child = parent->left;
	parent->left = child -> right;
	child->right = parent;
	return child;
}

t_AVLNode *rotate_left(t_AVLNode *parent)
{
	t_AVLNode *child = parent->right;
	parent->right = child->left;
	child->left = parent;

	return child;
}

t_AVLNode	*insert(t_AVLNode *node, int key)
{
	if(node == NULL)
		return(create_node(key));
	
	if(key < node->key)
		node->left = insert(node->left, key);
	else if(key > node->key)
		node->right = insert(node->right, key);
	else
		return node;
	
	int balance = get_balance(node);

	if(balance > 1 && key < node->left->key)
		return rotate_right(node);
	if(balance < -1 && key > node->right->key)
		return rotate_left(node);
	if(balance > 1 && key > node->left->key)
	{
		node->left = rotate_left(node->left);
		return rotate_right(node);
	}
	if(balance < -1 && key < node->right->key)
	{
		node->right = rotate_right(node->right);
		return rotate_left(node);
	}
	return node;
}
	
void preorder (t_AVLNode *root)
{
	if (root != NULL)
	{
		printf("[%d] ", root->key);
		preorder(root->left);
		preorder(root->right);
	}
}

int main()
{
	t_AVLNode *root = NULL;

	root = insert(root, 10);
	root = insert(root, 20);
	root = insert(root, 30);
	root = insert(root, 40);
	root = insert(root, 50);
	root = insert(root, 29);

	printf("전위 순회 결과 \n");
	preorder(root);

	return 0;
}
