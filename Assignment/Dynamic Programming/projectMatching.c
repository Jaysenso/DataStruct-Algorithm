#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct _listnode
{
 int vertex;
 struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graph{
    int V;
    int E;
    int *visited;
    int **adjMatrix;
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

void insertAdjVertex(ListNode** AdjList,int vertex);
void removeAdjVertex(ListNode** AdjList,int vertex);
int matching(Graph g);

void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);
void printQ(QueueNode *cur);
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
//////////////////////////////////
int fordFulkerson(Graph g, int source , int sink);
int DFS(Graph g, int source, int destination, int parent , int *parentsArray);
int min(int a, int b);
void printGraphMatrix(Graph g);



int min(int a, int b)
{
    return((a<b)?a:b);

}

 
int fordFulkerson(Graph g, int source , int sink)
{
    int flow, maximumFlow = 0;
    int i , j;
    //we will make a copy of Graph g and that will be our residual graph
    Graph resGraph;
    resGraph.E = g.E;
    resGraph.V = g.V;
    //malloc visited 1D array and adjmatrix 2D array
    resGraph.visited = (int *)malloc(resGraph.V * sizeof(int));
    resGraph.adjMatrix = (int **)malloc(resGraph.V * (sizeof(int*)));
    //initialize visited to 0 and make a copy of the adjMatrix
    for(i = 0; i < resGraph.V; i++)
    {
        resGraph.visited[i] = 0;
        resGraph.adjMatrix[i] = (int *)malloc(resGraph.V * (sizeof(int)));

        for(j = 0; j < resGraph.V; j++)
        {
            resGraph.adjMatrix[i][j] = g.adjMatrix[i][j];
        }
    }
    //create a parentsArray and initialize all entries to 0
    int *parentsArray = (int *)malloc(g.V * sizeof(int));
    for(i = 0; i < g.V; i++)
    {
        parentsArray[i] = 0;
    }


    //while there exists a path s->t (root node has no parent hence parent == -1)
    while(DFS(resGraph, source, sink, -1, parentsArray))
    {   
        //set flow to a very large value
        flow = INT_MAX;
        //we trace back the path that we took (sink -> source)
        for(i = sink; i != source; i = parentsArray[i-1])
        {   
            //j is the parent of the next node
            j = parentsArray[i - 1];
            flow = min(flow, resGraph.adjMatrix[j-1][i-1]);
        }
        //we trace back to source but this time round we will update the edges and reverse the direction
        for(i = sink; i != source; i = parentsArray[i-1])
        {
            j = parentsArray[i - 1];
            //cf(v,u) = cf(v,u) + f(v,u)
            resGraph.adjMatrix[i-1][j-1] += flow;
            //cf(u,v) = cf(u,v) - f(u-v)
            resGraph.adjMatrix[j-1][i-1] -= flow;
        }
        maximumFlow += flow;
        //we re-initialize all the arrays and DFS again
        for(i = 0; i < resGraph.V; i++)
        {
            resGraph.visited[i] = 0;
            parentsArray[i] = -1;
        }
    }
    return maximumFlow;
}



int DFS(Graph g, int source, int destination, int parent , int *parentsArray)
{
    //we will update current vertex as visited
    g.visited[source - 1] = 1;
    //this will be used in ford fulkeson algorithm -> to trace back to source
    parentsArray[source - 1] = parent;

    //we have found a path
    if(source == destination)
        return 1;

    //else we will visit all unvisited neighbors recursively and update parentsArray accordingly
    for(int i = 0; i < g.V; i++)
    {
        //if condition to make sure we are visiting a unvisited neighbor
        if(g.adjMatrix[source-1][i] == 1 && g.visited[i] == 0)
        {
            //once a path is found, we will return 1 to the caller
            if(DFS(g, i+1, destination, source, parentsArray))
                return 1;
        }
    }
    //else no path was found
    return 0;
}

/*
input :
    (first line) -> [students,projects,mentors]
    (second line) student 1 -> [no. of projects , no of mentors , projectChoice , mentorChoice]
    (third line) student n-> same as secnd line

psuedocode:
    1. collect the necessary inputs from the user (refer to input)
    2. build the graph with this direction : source -> project -> (student -> student) -> mentor -> sink (directed graph)
       NOTE: student -> student is a 1 to 1 mapping 
    3. duplicate the graph to make it a residual graph
    4. we will perform DFS and fordfulkerson on the residual graph to calculate max flow or matchings we can get from the source to sink 
*/
int main()
{
    int Prj, Std, Mtr; //Project, Student and Mentor;
    int maxMatch;
    scanf("%d %d %d", &Std, &Prj, &Mtr);
    scanf("\n");

    int i , j;
    int np,nm; //number of projects and number of mentors
    int projChoice, mentorChoice;
    
    int nodes = Prj + (Std * 2) + Mtr; //number of nodes in graph without source and sink 
    int source = 1; //source is our first vertex in the graph
    int sink = nodes + 2; //sink is the last vertex in the graph

    //initialize the graph
    Graph g;
    g.E = 0;
    g.V = sink;
    g.visited = (int *)malloc(g.V * sizeof(int));
    g.adjMatrix = (int **)malloc(g.V * (sizeof(int*)));

    for(i = 0; i < g.V; i++)
    {   
        //initialize visited
        g.visited[i] = 0;
        //create a 2D adjMatrix Array
        g.adjMatrix[i] = (int *)malloc(g.V * (sizeof(int)));
        //initialize it to 0
        for(j = 0; j < g.V; j++)
        {
            g.adjMatrix[i][j] = 0;
        }
    }

    //direct the source to all the projects
    for(i = 0; i < Prj; i++)
    {
       g.adjMatrix[source - 1][source + i] = 1;
       g.E++;
    }

    //We will build the adjMatrix by collecting the number of projects and mentors each student wants
    for(i = 0; i < Std; i++)
    {
        //number of projects & mentors
        scanf("%d %d" ,&np ,&nm);

        //we adding edges from projects -> students
        for(j = 0; j < np; j++)
        {
            scanf("%d",&projChoice);
            //we add the edges between the student and the project that hew ants
            g.adjMatrix[projChoice][1 + Prj + i] = 1;
            //increment the edge count after every successful insertion
            g.E++;
        }
        //we map student -> student : this will handle the max flow of 1
        g.adjMatrix[1 + Prj + i][1 + Prj + Std + i] = 1;
        g.E++;

        //we adding edges from students -> mentors
        for(j = 0; j < nm; j++)
        {
            scanf("%d", &mentorChoice);
            g.adjMatrix[1 + Prj + Std + i][1 + Prj + (Std * 2) + mentorChoice] = 1;
            g.E++;
        }
    }

    //direct all the mentors to sink
    for(i = 0; i < Mtr; i++)
    {
        //g.adjMatrix[mentors][n] where n is mentor number 
        g.adjMatrix[1 + Prj + (Std * 2) + i][sink - 1] = 1;
        g.E++;
    }

    //apply Ford Fulkerson algorithm
    // use DFS or BFS to find a path
    maxMatch = matching(g);
    printGraphMatrix(g);
    printf("%d\n", maxMatch);
    system("pause");

    return 0;
}

int matching(Graph g)
{
    int maximumMatching = fordFulkerson(g, 1, g.V);
    return maximumMatching;
}

void removeAdjVertex(ListNode** AdjList,int vertex)
{
 ListNode *temp, *preTemp;
 if(*AdjList != NULL)
 {
    if((*AdjList)->vertex ==vertex){//first node
      temp = *AdjList;
      *AdjList = (*AdjList)->next;
      free(temp);
      return;
    }
    preTemp = *AdjList;
    temp = (*AdjList)->next;
    while(temp!=NULL && temp->vertex != vertex)
    {
      preTemp= temp;
      temp = temp->next;
    }
    preTemp->next = temp->next;
    free(temp);
   }
}

void insertAdjVertex(ListNode** AdjList,int vertex)
{
  ListNode *temp;
  if(*AdjList==NULL)
  {
     *AdjList = (ListNode *)malloc(sizeof(ListNode));
     (*AdjList)->vertex = vertex;
     (*AdjList)->next = NULL;
  }
  else{
     temp = (ListNode *)malloc(sizeof(ListNode));
     temp->vertex = vertex;
     temp->next = *AdjList;
     *AdjList = temp;
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

void printQ(QueueNode *cur){
 if(cur==NULL) printf("Empty");

 while (cur != NULL){
    printf("%d ", cur->vertex);
    cur = cur->next;
  }
 printf("\n");
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


void printGraphMatrix(Graph g)
{
    int i,j;
    //Print the rows first.
    printf("Adjacency Matrix\n");
    //Print divider.
    for(i = 0; i < g.V; i++)
    {
        printf("---------");
    }
    printf("\n|  \t|");
    for(i = 0; i < g.V; i++)
    {
        printf("\t%d",i+1);
    }
    printf(" |\n");
    //Print divider.
    for(i = 0; i < g.V; i++)
    {
        printf("---------");
    }
    printf("\n");
    for(i=0;i<g.V;i++){
        //Print divider.
        printf("| %d\t|",i+1);
        for(j=0;j<g.V;j++)
            printf("\t%d",g.adjMatrix[i][j]);
        printf("  |\n");
    }
    //Print divider.
    for(i = 0; i < g.V; i++)
    {
        printf("---------");
    }
    printf("\n");
}