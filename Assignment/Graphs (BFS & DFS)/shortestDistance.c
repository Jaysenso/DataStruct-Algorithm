#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;

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

int BFS (Graph G, int v, int w);

void printGraphList(Graph );

// You should not change the prototypes of these functions
void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);

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
    printf("Enter two vertices for finding their shortest distance:\n");
    scanf("%d %d", &i, &j);

    int d = BFS(g,i,j);
	
    if(d==-1)
        printf("%d and %d are unconnected.\n",i,j);
    else
        printf("The shortest distance is %d\n",d);
    printGraphList(g);

    system("pause");
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

void enqueue(Queue *qPtr, int item) {
    QueueNode *newNode;
    newNode = malloc( sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = item;
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

/*
ALGORITHM EXPLANATION:
-> graph is presented in an adjacency list
-> OUTPUT : the shortest distance between source node and destination code (need some sort of counter)
->we need a way to keep track of visited nodes so we do not traverse visited node again
-> FIFO queue is used to push children nodes of popped node

-> if successful -> return the distance/no. of nodes between source and destination nodes
-> else if unsuccessful attempt -> return -1

STEPS:
    1. create a temp FIFO Queue 'q' and initialize it
    2. for loop and search for our source node in the adjacency list
    3. curr = curr -> next to traverse the linked list (those will be pushed into the queue as "child nodes")
        3.1 -> we will pop the first item in the queue and enqueue its children, and label the popped
            node as "visited", this will be progress "recursively" till we meet this condition
                -> Queue "q" is empty
*/


int BFS (Graph g, int v, int w) // int v -> source node , int w -> destination node
{   
    //graph is empty, we will return -1;
    if(g.V == 0)
        return -1;
    
    //means that source node has not adjacent nodes, there will be no path to destination node
    if(g.list[v-1] == NULL)
        return -1;

    //the source == destination , distance with itself is 0
    if (v == w)
        return 0;


    //declarations    
    ListNode *currentNode;

    int i ,parentvertex, shortestPath = 0,count = 0;
    int vertices = g.V, edges = g.E;

    int *visitedNodes;
    int *distanceCost;

    //create a FIFO queue -> whenever we pop a node, we will insert it childrens into the queue
    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    //arrays initialization -> index of array == node 's vertex
    visitedNodes = (int *)malloc(vertices * sizeof(int));
    distanceCost = (int *)malloc(vertices * sizeof(int));

    for(i = 0; i < vertices; i++)
    {
        visitedNodes[i] = 0;    
        distanceCost[i] = 0;
    }
    
    //enqueue the source node and mark it as visited
    enqueue(&q, v);
    visitedNodes[v - 1] = 1;
           
    //keep pushing popped node's children 
    while(!isEmptyQueue(q))
    {  
        parentvertex = getFront(q);
        //access parentVertex 's adjacency list
        currentNode = g.list[parentvertex - 1];
        dequeue(&q);

        if(currentNode == NULL)
            continue;

        //else we will enqueue all the adjacency nodes (aka child nodes) of popped node
        while(currentNode != NULL)
        {
            //if current vertex is unvisited, we will enqueue it into the queue
            if(visitedNodes[currentNode->vertex - 1] == 0)
            {   
                enqueue(&q, currentNode->vertex);
                //update the visitNodes and distanceCost from source node
                visitedNodes[currentNode->vertex - 1] = 1;
                //currentIndex stores the parent node index
                distanceCost[currentNode->vertex - 1] = distanceCost[parentvertex - 1] + 1;

                //we found our destination node ->proceed to free
                if(currentNode->vertex == w)
                {
                    shortestPath = distanceCost[currentNode->vertex - 1];
                    free(visitedNodes);
                    free(distanceCost);
                    
                    return shortestPath;
                }
            }
            //enqueue the current node and update visitedNodes and distanceCost
            currentNode = currentNode->next;
        }
    }
    
    return -1;
}
