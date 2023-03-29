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
    ListNode **list;
}Graph;

typedef ListNode QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

typedef struct _stack
{
	int size;
	StackNode *head;
} Stack;

int CC (Graph g);

void printGraphList(Graph );

// You should not change the prototypes of these functions
void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
//////////////////////////////////

int main()
{
    Graph g;
    int i,j;
    ListNode *temp;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.list = (ListNode **) malloc(g.V*sizeof(ListNode *));

    for(i=0;i<g.V;i++)
        g.list[i] = NULL;

    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&i,&j)==2)
    {
        i=i-1;

        if(g.list[i]==NULL){
            g.list[i] = (ListNode *)malloc(sizeof(ListNode));
            g.list[i]->vertex = j;
            g.list[i]->next = NULL;
        }
        else{
            temp = (ListNode *)malloc(sizeof(ListNode));
            temp->next = g.list[i];
            temp->vertex = j;
            g.list[i] = temp;
        }
        g.E++;
        printf("Enter two vertices which are adjacent to each other:\n");
    }
    scanf("%*c");

    int res = CC(g);
    if(res ==1)
        printf("The graph is strongly connected.\n");
    else
        printf("The graph is not strongly connected.\n");

    printGraphList(g);
    return 0;
}

void printGraphList(Graph g){
    int i;
    ListNode* temp;

    for(i=0;i<g.V;i++)
    {
        printf("%d:\t",i+1);
        temp = g.list[i];
        while(temp!=NULL){
            printf("%d -> ",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void enqueue(Queue *qPtr, int vertex) {
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = vertex;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr) {
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return 1;
    }
}

int getFront(Queue q){
    return q.head->vertex;
}

int isEmptyQueue(Queue q) {
    if(q.size==0) return 1;
    else return 0;
}

void removeAllItemsFromQueue(Queue *qPtr)
{
	while(dequeue(qPtr));
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

/*
ALGORTHIM EXPLANATION
    NOTE: DFS guarantees to visit all nodes -> we can use this behavior to determine whether the input graph is strongly connected
    1. Perform DFS on every vertex
    2. As long as a DFS on any of vertex does not visit all the nodes, we will return 0 -> means that its not strongly connected
    3. However, if we DFS-ed all the vertices and visited all the nodes -> we the graph is strongly connected from every vertices.

*/
int CC (Graph g)
{
    Stack S;
    S.head = NULL;
    S.size = 0;

    ListNode *currentNode;

    int vertices = g.V , edges = g.E;
    int stronglyConnected = 1;
    int unVisitedNeighbor , currentVertex , i;
    int * visitedNodes;

    //graph with 0 vertex ==> vascously strongly connected by its own (sanity check)
    if(vertices == 0)
        return 1;
    
    if(edges == 0 && vertices > 1)
        return 0;

    //create 1D array to keep track of what have been visited 
    visitedNodes = (int *)calloc(vertices , sizeof(int));

    //i represents the ID of the vertex that we are conducting DFS on
    for(i = 1; i <= vertices; i++)
    {
        //we will push the current vertex into the stack
        push(&S, i);

        //we will update the visited status 
        visitedNodes[i - 1] = 1;

        while(!isEmptyStack(S))
        {
            currentVertex = peek(S);
            currentNode = g.list[currentVertex - 1];
            unVisitedNeighbor = 0; // <- this will only be updated when we push a unvisited node into the visited Array

            //current vertex has no connection with other nodes -> is not a strongly connected graph
            if(currentNode == NULL)
                return 0;

            while(currentNode != NULL)
            {
                //we will push unvisited child node into the stack & update the visitedNodes array
                if(visitedNodes[currentNode->vertex - 1] == 0)
                {
                    visitedNodes[currentNode->vertex - 1] = 1;
                    push(&S, currentNode->vertex);
                    unVisitedNeighbor = 1; 
                }
                currentNode = currentNode->next;
            }

            //we have visited all the neighbouring nodes -> we will backtrack to the prev node by popping off the stack
            if(unVisitedNeighbor == 0) 
            {
                pop(&S);
            }
        }
        //we will traverse the 'visitedNodes' array and check if the DFS was able to visit all the vertices
        for(i = 0; i < vertices; i++)
        {
            //if theres an unvisited vertex -> we know the graph is not strongly connected
            if(visitedNodes[i] == 0)
            {
                stronglyConnected = 0;
            }
            //we will reset all the visitedNodes as we traverse to find the one that we didnt visit
            visitedNodes[i] = 0;
        }

        if(stronglyConnected == 0)
        {
            free(visitedNodes);
            return 0;
        }

    } 
    return 1;
}

