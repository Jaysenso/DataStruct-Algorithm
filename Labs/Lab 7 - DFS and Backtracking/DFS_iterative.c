#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graph{
    int V;
    int E;
    int **matrix;
}Graph;

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} Stack;

// You should not change the prototypes of these functions
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
////GRAPH////////////////////////////////////////////
void printGraphMatrix(Graph );
////////////////////////////////////////////

void DFS_I (Graph , int );

int main()
{
    Graph g;
    int i,j;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.matrix[i] = (int *)malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++)
       for(j=0;j<g.V;j++)
           g.matrix[i][j] = 0;

    int V1, V2;
    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.matrix[V1-1][V2-1] = 1;
            g.matrix[V2-1][V1-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other:\n");
    }
    scanf("%*c");
    printf("Enter a start vertex for DFS:\n");
    scanf("%d", &i);
    printGraphMatrix(g);
    DFS_I(g,i);
    system("pause");
    return 0;
}

void DFS_I (Graph g, int v)// v <- starting vertex
{
    if (v <= 0)
        return;
    
    Stack s;
    s.head = NULL;
    s.size = 0;
    int i , neighbour , currentVertex , adjacencyVertex;
    int size = g.V;
    int *visited = (int *)malloc(size * sizeof(int));

    //initialize visited Array
    for(i = 0; i< size; i++){
        visited[i] = 0;
    }
    //push root vertex and update visited
    printf("%d->",v);
    push(&s,v);
    visited[v - 1] = 1;

    while(!isEmptyStack(s)){
        //we only want to push 1 neighbour into the stack 
        adjacencyVertex = 0;
        currentVertex = peek(s);
        
        //loop through currentVertex 's neighbours
        for(neighbour = 0; neighbour < size; neighbour++){
            //check if its a unvisited neighbour
            if(g.matrix[currentVertex-1][neighbour] == 1 && visited[neighbour] != 1){
                //we print before we push, so we can trace the path from starting vertex to the depth
                printf("%d->",neighbour+1);
                push(&s, neighbour+1);
                visited[neighbour]=1;
                adjacencyVertex = 1;
                //the moment we found a neighbour, we just break out of the for loop
                break;
            }
        }
        //if no neighbour is found, we backtrack all the way to last intersection node
        if(!adjacencyVertex){
            pop(&s);
        }
    }
}

void printGraphMatrix(Graph g)
{
    int i,j;

    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.matrix[i][j]);
        printf("\n");
    }

}

void push(Stack *sPtr, int vertex)
{
	StackNode *newNode;
    newNode= malloc(sizeof(StackNode));
    newNode->vertex = vertex;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if(sPtr==NULL || sPtr->head==NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

int isEmptyStack(Stack s)
{
     if(s.size==0) return 1;
     else return 0;
}

int peek(Stack s){
    return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
	while(pop(sPtr));
}
