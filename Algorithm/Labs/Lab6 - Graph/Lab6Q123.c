#include <stdio.h>
#include <stdlib.h>

enum GraphType {ADJ_MATRIX, ADJ_LIST}; // Types of Graph Representation

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;

union GraphForm{
    int **matrix;
    ListNode **list;
};

typedef struct _graph{
    int V;
    int E;
    enum GraphType type;
    union GraphForm adj;
}Graph;

void printGraphMatrix(Graph );
void adjM2adjL(Graph *);
void adjL2adjM(Graph *);
void printGraphList(Graph );
void calDegreeV(Graph,int *);
void printDegreeV(int *,int );

int main()
{
    Graph g;
    int i,j;

    int* degreeV;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.adj.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.adj.matrix[i] = (int *)malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++)
        for(j=0;j<g.V;j++)
            g.adj.matrix[i][j] = 0;
    g.type = ADJ_MATRIX;

    degreeV = (int *) malloc(g.V*sizeof(int));
    for(i=0;i<g.V;i++)
        degreeV[i]=0;

    int V1, V2;
    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.adj.matrix[V1-1][V2-1] = 1;
            g.adj.matrix[V2-1][V1-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other:\n");
    }

    calDegreeV(g,degreeV);

    printGraphMatrix(g);
    printDegreeV(degreeV,g.V);

    //gtype check

    /*if(g.type == ADJ_LIST)
        printf("g is ADJ_LIST");
    else if (g.type == ADJ_MATRIX)
        printf("g is ADJ_MATRIX");*/

    
    adjM2adjL(&g);

    calDegreeV(g,degreeV);

    printGraphList(g);
    // printDegreeV(degreeV,g.V);

    // adjL2adjM(&g);
    // printGraphMatrix(g);

    return 0;
}

void printGraphMatrix(Graph g)
{
    int i,j;
    if(g.type == ADJ_LIST) {printf("Error"); return;}

    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.adj.matrix[i][j]);
        printf("\n");
    }

}

void printDegreeV(int *degreeV,int V)
{
    int i;
    for(i=0;i<V;i++)
        printf("%d: %d degree\n",i+1,degreeV[i]);
}

void printGraphList(Graph g){
    int i;
    ListNode* temp;

    if(g.type == ADJ_MATRIX) {printf("Error"); return;}

    for(i=0;i<g.V;i++)
    {
        printf("%d:\t",i+1);
        temp = g.adj.list[i];
        while(temp!=NULL){
            printf("%d -> ",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void adjM2adjL(Graph *g)
{
    if (g->type == ADJ_LIST)
    {
        printf("Error");
        return;
    }

    int i,j;
    int vertices = g->V;
    ListNode *newNode, *curr, * tail;
    ListNode **adjList;

    //2D array malloc
    adjList = (ListNode **)malloc(vertices * sizeof(ListNode));
    //initialize the 2D array
    for(i = 0; i < vertices; i++)
    {
        adjList[i] = NULL;
    }


    for(i = 0; i < vertices; i++)
    {
        for(j = 0; j < vertices; j++)
        {
            if(g->adj.matrix[i][j] == 1)
            {
                //malloc a new node to link to the linked list and initialize it.
                ListNode *newNode = malloc(sizeof(ListNode));
                newNode->vertex = j + 1;
                newNode->next = NULL;
                
                //if the head is NULL -> we will update the head pointer to point to
                //the 1st node
                if(adjList[i] == NULL)
                {
                    adjList[i] = newNode;
                    //Store a tail so both the head and tail are the same.
                    tail = newNode;
                }
       

                //else we will use curr to traverse to the last Node and add the NewNode to the back
                else
                    {
                        
                        tail->next = newNode;
                        tail = newNode;
                    }
            }
        }
    }

    for (i = 0; i < g->V; i++)
    {
        free(g->adj.matrix[i]);
    }
    free(g->adj.matrix);


    g->adj.list = adjList;
    g->type = ADJ_LIST;
        
}

void adjL2adjM(Graph *g){
	// Question 2
    // Write your code here

}

void calDegreeV(Graph g, int *degreeV)
{
	// Question 3
    // Write your code here
}

