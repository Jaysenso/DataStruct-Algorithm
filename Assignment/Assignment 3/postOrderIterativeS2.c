//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
int item;
struct _bstnode *left;
struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
BSTNode *data;
struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS2(BSTNode *root);

void insertBSTNode(BSTNode **node, int value);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
int c, i;
c = 1;

//Initialize the Binary Search Tree as an empty Binary Search Tree
BSTNode * root;
root = NULL;

printf("1: Insert an integer into the binary search tree;\n");
printf("2: Print the post-order traversal of the binary search tree;\n");
printf("0: Quit;\n");

insertBSTNode(&root, 20);
insertBSTNode(&root, 15);
insertBSTNode(&root, 50);
insertBSTNode(&root, 10);
insertBSTNode(&root, 18);
insertBSTNode(&root, 25);
insertBSTNode(&root, 80);

while (c != 0)
{
    printf("Please input your choice(1/2/0): ");
    scanf("%d", &c);

    switch (c)
    {
    case 1:
        printf("Input an integer that you want to insert into the Binary Search Tree: ");
        scanf("%d", &i);
        insertBSTNode(&root, i);
        break;
    case 2:
        printf("The resulting post-order traversal of the binary search tree is: ");
        postOrderIterativeS2(root); // You need to code this function
        printf("\n");
        break;
    case 0:
        removeAll(&root);
        break;
    default:
        printf("Choice unknown;\n");
        break;
    }

}

return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void postOrderIterativeS2(BSTNode *root)
{   
    if (root == NULL)
        return; 

    //initialize the two stacks    
    Stack s1,s2;
    s1.top = NULL;
    s2.top = NULL;
    BSTNode *popped;

    //push root to first stack
    push(&s1,root);
    //loop while first stack is not empty
    while(!isEmpty(&s1))
    {
        //pop a node from first stack
        popped = pop(&s1);
        //push it to second stack
        push(&s2,popped);
        //push left children of the popped node to first stack
        if (popped->left != NULL)
            push(&s1,popped->left);
        //push right children of the popped node to first stack
        if (popped->right!= NULL)    
            push(&s1,popped->right);
    }   
    //at this point, all the nodes values will be postorder and ready to be printed
    while(!isEmpty(&s2))
    {
        popped = pop(&s2);

        if (popped != NULL)
            printf("%d ", popped->item);
    }
}

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
if (*node == NULL)
{
    *node = malloc(sizeof(BSTNode));

    if (*node != NULL) {
        (*node)->item = value;
        (*node)->left = NULL;
        (*node)->right = NULL;
    }
}
else
{
    if (value < (*node)->item)
    {
        insertBSTNode(&((*node)->left), value);
    }
    else if (value >(*node)->item)
    {
        insertBSTNode(&((*node)->right), value);
    }
    else
        return;
}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
StackNode *temp;

temp = malloc(sizeof(StackNode));

if (temp == NULL)
    return;
temp->data = node;

if (stack->top == NULL)
{
    stack->top = temp;
    temp->next = NULL;
}
else
{
    temp->next = stack->top;
    stack->top = temp;
}
}


BSTNode * pop(Stack * s)
{
StackNode *temp, *t;
BSTNode * ptr;
ptr = NULL;

t = s->top;
if (t != NULL)
{
    temp = t->next;
    ptr = t->data;

    s->top = temp;
    free(t);
    t = NULL;
}

return ptr;
}

BSTNode * peek(Stack * s)
{
StackNode *temp;
temp = s->top;
if (temp != NULL)
    return temp->data;
else
    return NULL;
}

int isEmpty(Stack *s)
{
if (s->top == NULL)
    return 1;
else
    return 0;
}


void removeAll(BSTNode **node)
{
if (*node != NULL)
{
    removeAll(&((*node)->left));
    removeAll(&((*node)->right));
    free(*node);
    *node = NULL;
}
}