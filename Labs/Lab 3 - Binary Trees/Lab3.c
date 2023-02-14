////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////


typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;

} BTNode;

////////////////////////////////////////////////////////////////////


void mirrorTree(BTNode *node);

void printSmallerValues(BTNode *node, int m);
int smallestValue(BTNode *node);
int hasGreatGrandchild(BTNode *node);

void printTree_InOrder(BTNode *node);

////////////////////////////////////////////////////////////////////

int main(int argc, const char * argv[]){

	int i;
	BTNode *root, *root2;
	BTNode btn[15];

	// Create the tree in Q1
	// Using manual dynamic allocation of memory for BTNodes

	root = malloc(sizeof(BTNode));
	root->item = 4;

	root->left = malloc(sizeof(BTNode));
	root->left->item = 5;

	root->right = malloc(sizeof(BTNode));
	root->right->item = 2;

	root->left->left = NULL;

	root->left->right = malloc(sizeof(BTNode));
	root->left->right->item = 6;

	root->left->right->left = NULL;
	root->left->right->right = NULL;

	root->right->left = malloc(sizeof(BTNode));
	root->right->left->item = 3;

	root->right->right = malloc(sizeof(BTNode));
	root->right->right->item = 1;

	root->right->left->left = NULL;

	root->right->left->right = NULL;

	root->right->right->left = NULL;

	root->right->right->right = NULL;

	printTree_InOrder(root);
	printf("\n");
	mirrorTree(root);
	printTree_InOrder(root);
	printf("\n\n");

	//question 2
	printf("\n input m for question 2:");
	scanf("%d", &i);
	printf("the values smaller than %d are:", i);
	printSmallerValues(root, i);
	printf("\n\n");

	//question 3
	printf("The smallest value in the tree is %d:\n", smallestValue(root));

	//question 4
	// Create a tree for Q4: Tall enough so some nodes have great-grandchildren
	// Use array of BTNodes, create tree by linking nodes together
	for (i = 0; i <= 6; i++){
		btn[i].item = i;
		btn[i].left = &(btn[i * 2 + 1]);
		btn[i].right = &(btn[i * 2 + 2]);
	}

	for (i = 7; i <= 14; i++){
		btn[i].item = i;
		btn[i].left = NULL;
		btn[i].right = NULL;
	}
	root2 = &btn[0];

	printf("The tree for question 4 visited by in-order is \n");
	printTree_InOrder(root2);
	printf("\nthe values stored in all nodes of the tree that have at least one great-grandchild are: ");

	hasGreatGrandchild(root2);

	return 0;
}
/* ALGORITHM EXPLANATION: Recursive function
    1. we will perform sanity check - this will be incharge of pulling us out of the recursion
    2. we will create a temporary pointer that stores node->left value for easier swapping
    3. we will then call mirrorTree twice (for left & right nodes) -> to travel through the tree by level
    4. This will only terminate when i reached NULL -> taken care by the sanity check earlier
    5. Similarly for mirrorTree(node->right), once im out of this function, we know that we are at the same level
        to perform swapping.
    example: 
             5       5
            / \  -> / \
           4  6    6  4
*/
void mirrorTree(BTNode *node){

	//
    if (node == NULL)
        return;
    else
        {
            BTNode *temp;
            mirrorTree(node->left);
            mirrorTree(node->right);

            temp = node->left;
            node->left = node->right;
            node->right = temp;
        }

}

int hasGreatGrandchild(BTNode *node){

	// write your code here

}
/*
ALGORITHM EXPLANATION: 
    1. traverse through the tree
    2. stops once we hits the last node and compare the value with m
    3. if current node < m , we will print current node
    4. then we will traverse back up to root node as we print the smaller values
*/
void printSmallerValues(BTNode *node, int m){

	// write your code here
    if (node == NULL)
        return;
    else
    {  
        printSmallerValues(node->left, m);
        printSmallerValues(node->right, m);

        if (node->item < m)
            printf(" %d ", node->item);
    }

}
/*
ALGORITHM EXPLANATION
1. traverse to the bottom of the tree
2. if (node == NULL) -> we will return a very large int number (100000)
3. if (node != NULL)    */

int smallestValue(BTNode *node) {
	int l, r;

	// write your code here
    //if node == NULL, we will return a very large number to be compared to the available node
    if (node == NULL)
        return 100000;


    l = smallestValue(node->left);
    r = smallestValue(node->right);
    /* if left / right node doesnt exist, it will return 100000, then the node on the opposite will be compared
    to this 100000 value and return itself */

    // check if we have a right node 
    if (l < node->item && l < r)
        return l;
    // check if we have a left node
    else if ( r < node->item && r < l) 
        return r;
    
    // check if we have reached the root node
    else
        return node->item;

}


//////////////////////////////////////////////////////////////////

void printTree_InOrder(BTNode *node){

	if (node == NULL) return;
	printTree_InOrder(node->left);
	printf("%d, ", node->item);
	printTree_InOrder(node->right);
	return;
}
