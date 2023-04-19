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

    adjM2adjL(&g);

    calDegreeV(g,degreeV);

    printGraphList(g);
    printDegreeV(degreeV,g.V);

    adjL2adjM(&g);
    printGraphMatrix(g);
    system("pause");
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
/*
    BREAKDOWN:
    1. main insert the edges and vertices into an adj Matrix (is a bidrectional graph)
    2. we will double for loop through the ajacency matrix and populate into a temp list
    3. then we will free g.adjmatrix and insert our newly created adjList to g.
*/
void adjM2adjL(Graph *g){

    //we check if graph exists or 
    if(g == NULL || g->V == 0)
        return;

    int i,j;
    int size = g->V;

    //initialize an array of listnode pointers
    ListNode **adjList = (ListNode **)malloc(size * sizeof(ListNode));
    for(i = 0; i < size; i++){
        adjList[i] = NULL;
    }
    //traverse the adjacency matrix 
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++)
        {
            //if theres edges between 2 vertices
            if(g->adj.matrix[i][j] == 1){

                ListNode* newNode = (ListNode *)malloc(sizeof(ListNode));
                newNode->vertex = j+1;
                newNode->next = NULL;

                if(adjList[i] == NULL){
                    adjList[i] = newNode;
                }
                else{
                    newNode->next = adjList[i];
                    adjList[i] = newNode;
                }
            }
        }
    }
    //we will free g.adjmatrix since its union(only one datastruct can exists at one time)
    for (i = 0; i < size; i++)
    {
        free(g->adj.matrix[i]);
    }
    free(g->adj.matrix);

    //we will then point g->adj to the newly created list and update g.type 
    g->adj.list = adjList;
    g->type = ADJ_LIST;

}

void adjL2adjM(Graph *g){

    //check if graph exists or the number of vertices > 1
    if(g == NULL || g->V == 0){
        return;
    }
    int i, j;
    int size = g->V;

    ListNode *curr;

    //initialize 2D adjMatrix
    int **adjMatrix = (int **)malloc(size * sizeof(int*));
    for(i = 0; i < size; i++){  
        adjMatrix[i] = (int *)malloc(sizeof(int));
        for(j = 0; j < size; j++)
        {
            adjMatrix[i][j] = 0;
        }
    }
    //loop through the adjacency list and populate the matrix
    for(i = 0; i < size; i++){   
        //theres no adjacency nodes
        if(g->adj.list[i] == NULL)
            continue;

        curr = g->adj.list[i];
        while(curr != NULL)
        {
            adjMatrix[i][curr->vertex - 1] = 1;
            curr = curr->next;
        }
    }

    //free the adjList
    for(i = 0; i < size; i++){
        free(g->adj.list[i]);    
    }
    free(g->adj.list);

    //update g->adj data struct and type
    g->adj.matrix = adjMatrix;
    g->type = ADJ_MATRIX;
}

void calDegreeV(Graph g, int *degreeV)
{
    if(g.V == 0)
        return;
    
    int i,j;
    int size = g.V , edgeCount;

    //reinitialize degreeV
    for(i = 0; i < size; i++){
        degreeV[i] = 0;
    }

    //handle each g.type to calculate degreeV
    if(g.type == ADJ_MATRIX){
        //loop through the matrix and check each vertices' edges 
        for(i = 0; i < size; i++){
            edgeCount = 0;
            for(j = 0; j < size; j++)
            {
                if(g.adj.matrix[i][j] == 1){
                    edgeCount++;
                }
            }
            //once we done counting the edge, we populate inside degreeV array with index corresponding
            //to its vertex number
            degreeV[i] = edgeCount;
        }
    }
    else if(g.type == ADJ_LIST){
    
        ListNode* curr;
        //loop through the entire adjList starting from vertex 1 (index 0) - vertex n
        for(i = 0; i < size; i++){
            curr = g.adj.list[i];
            edgeCount = 0;
            //travel down the linked list at that index and count the number of nodes
            while(curr !=NULL){
                edgeCount++;
                curr = curr->next;
            }
            //populate into degreeV
            degreeV[i] = edgeCount;
        }
    }
}

