//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////

typedef struct _btnode{
int item;
struct _btnode *left;
struct _btnode *right;
} BTNode;

///////////////////////////////////////////////////////////////////////

void insertBSTNode(BTNode **node, int value);
void printBSTInOrder(BTNode *node);
int isBST(BTNode *node, int min, int max);
BTNode *removeBSTNode(BTNode *node, int value);
BTNode *findMin(BTNode *p);

///////////////////////////////////////////////////////////////////////

int main(){
	int i=0;

	BTNode *root=NULL;

	//question 1
	do{
		printf("input a value you want to insert(-1 to quit):");

		scanf("%d",&i);
		if (i!=-1)
			insertBSTNode(&root,i);
	}while(i!=-1);

	//question 2
	printf("\n");
	printBSTInOrder(root);

	//question 3
	if ( isBST(root,-1000000, 1000000)==1)
		printf("It is a BST!\n");
	else
		printf("It is not a BST!\n");

	//question 4
	do{
		printf("\ninput a value you want to remove(-1 to quit):");
		scanf("%d",&i);
		if (i!=-1)
		{
			root=removeBSTNode(root,i);
			printBSTInOrder(root);
		}
	}while(i!=-1);


	return 0;
}

//////////////////////////////////////////////////////////////////////

void insertBSTNode(BTNode **node, int value)
{	
    BTNode *newNode;
    // If the current node is NULL, means the tree is empty then we need to malloc.
    if(*node == NULL)
    {
        newNode = malloc(sizeof(BTNode));
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->item = value;

        *node = newNode;
        return;
    }

    //BST only accept unique value
    if((*node)->item == value)
    {
        printf("Can't insert %d value into the BST, already exists!", value);
        return;
    }

    if(value < (*node)->item)
        insertBSTNode(&((*node)->left),value);
    else
        insertBSTNode(&((*node)->right),value);

}

//////////////////////////////////////////////////////////////////////

void printBSTInOrder(BTNode *node)
{
	if (node == NULL)
        return;

    printBSTInOrder(node->left);
    printf("%d",node->item);
    printBSTInOrder(node->right);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int isBST(BTNode *node, int min, int max) // the item stored in node has to be smaller than max and larger than min
{
	if (node == NULL)
        return 1;
    
    int l,r;
    if(min < node->item && node->item < max)
    {
        l = isBST(node->left,min,node->item);
        r = isBST(node->right,node->item,max);

        return l && r;
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BTNode *removeBSTNode(BTNode *node, int value)
{
	// write your code here
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BTNode *findMin(BTNode *p)
{
	// write your code here
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////