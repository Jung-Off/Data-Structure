#include <stdio.h>
#include <stdlib.h>

typedef struct s_TreeNode
{
	int					data;
	struct s_TreeNode	*left; // >> t_TreeNode 로 하면 안됨?
	struct s_TreeNode	*right;
}				t_TreeNode;

//선언되기 전과 선언되고 나서 
//선언이 되고 난 이후 구조체 안에 t_... ...; 
//선언을 하는 중 struct s_... ...;

t_TreeNode	g_n1 = {05, NULL, NULL};
t_TreeNode	g_n2 = {15, &g_n1, NULL};
t_TreeNode	g_n3 = {35, NULL, NULL};
t_TreeNode	g_n4 = {95, NULL, NULL};
t_TreeNode	g_n5 = {93, &g_n3, &g_n4};
t_TreeNode	g_n6 = {17, &g_n2, &g_n5};

t_TreeNode	*g_root = &g_n6;

//중위순회

void	inorder(t_TreeNode *root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("[%d] ", root->data);
		inorder(root->right);
	}
}

void	preorder(t_TreeNode *root)
{
	if (root != NULL)
	{
		printf("[%d] ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void	postorder(t_TreeNode *root)
{
	if (root != NULL)
	{
		postorder(root->left);
		postorder(root->right);
		printf("[%d] ", root->data);
	}
}

int	main(void)
{
	printf("중위 순회 = ");
	inorder(g_root);
	printf("\n");
	printf("전위 순회 = ");
	preorder(g_root);
	printf("\n");
	printf("후위 순회 = ");
	postorder(g_root);
	printf("\n");
}
