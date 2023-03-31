#include<stdio.h>
#include <stdlib.h>
  
int* city_population (int N, int* population, int** road, int Q, int** cities);

int main() 
{
    int N;
    scanf("%d", &N);
    int i_population;

    //population 1D array
    int *population = (int *)malloc(sizeof(int)*(N));
    for(i_population = 0; i_population < N; i_population++)
    	scanf("%d", &population[i_population]);

    //roads between cities 2D aray
    int i_road, j_road;
    int **road = (int **)malloc((N-1)*sizeof(int *));

    for(i_road = 0; i_road < N-1; i_road++)
    {
    	road[i_road] = (int *)malloc((2)*sizeof(int));
    }

    for(i_road = 0; i_road < N-1; i_road++)
    {
    	for(j_road = 0; j_road < 2; j_road++)
    	{
    		scanf("%d", &road[i_road][j_road]);
    	}
    }

    // Number of queries
    int Q;
    scanf("%d", &Q);
    int i_cities, j_cities;
    int **cities = (int **)malloc((Q)*sizeof(int *));
    for(i_cities = 0; i_cities < Q; i_cities++)
    {
    	cities[i_cities] = (int *)malloc((3)*sizeof(int));
    }
    for(i_cities = 0; i_cities < Q; i_cities++)
    {
    	for(j_cities = 0; j_cities < 3; j_cities++)
    	{
    		scanf("%d", &cities[i_cities][j_cities]);
    	}
    }

    int* out_ = city_population(N, population, road, Q, cities);
    printf("%d", out_[0]);
    int i_out_;
    for(i_out_ = 1; i_out_ < Q; i_out_++)
    	printf("\n%d", out_[i_out_]);

system("pause");
}


/*  
FUNCTION DESCRIPTION: 
    count[i] is the number of cities with population less than or equal to cities[i][2] 
    Start of city is denoted by cities[i][0] and end of city is denoted by cities[i][1]
    The road is undirected and there is only one road between two cities
    Traverse the start city to the end city with the road
    Traverse with depth first search with recursion
    Return an array of count of cities that satisfy the above condition

 ALGORITHM EXPLANATION:
    1. perform DFS based of the U and V in the queries 2D array 
    2. tally it to the population array and check if the individual populations <= W (the maximum number of population)
    3. the function returns a 1D array with the number of cities fulfilling the requirement corresponding to the query index

NOTE: we need to come up with a data struct to stores all our adjacency nodes -> adjacency list 

Consider N = 3 , population = [1,2,3], road = [[1,2],[2,3]], Q = 2, cities = [[1,3,2]]
The given query is the number of cities in the path from 1 to 3 that have a population of at most2
cities lie in the path are [1,2,3]. so the answer will return 2
*/
typedef struct _listnode
{
    int city_ID;
	struct _listnode *next;
} ListNode;

typedef struct _graph
{
    int numOfCities;
    int *visited;
    ListNode **adjList;
} Graph;

int DFS(ListNode **adjList, int source, int destination, int maxPopulationSize, int *population , int *count , int * visited);
void adjacencyList(ListNode **adjList, int N);


int DFS(ListNode **adjList, int source, int destination, int maxPopulationSize, int *population , int *count , int * visited)
{
    //currentNode : parent Node
    ListNode *currentNode = adjList[source - 1];
    int cityCount;

    //updates the visited table to mark the source city as visited.
    visited[source - 1] = 1;

    //if the source 's population is under maxPopulationSize , we will increment our count pointer 
    if(population[source - 1] <= maxPopulationSize)
        (*count)++;

    //source city is equal to the destination city, then the function has reached the destination and returns 1
    if(source == destination)
        return 1;

    //else we will traverse the adjacency list of source node and call DFS function on its unvisited neighbors.
    while(currentNode != NULL)
    {   
        //we will store *count in temp variable 'cityCount'
        cityCount = *count;

        if(visited[currentNode->city_ID - 1] == 0)
        {   
            //If the DFS function finds the destination city in its recursive call, then it updates the 'count' pointer 
            //variable with the CityCount and returns 1 to indicate that it has reached the destination city.
            if(DFS(adjList , currentNode->city_ID , destination , maxPopulationSize , population , &cityCount , visited))
            {
                //we will only update *count == cityCount if we have found destination/end vertex
                //this will propagate upwards back to the original function call
                *count = cityCount;
                return 1;
            }
        }
        currentNode  = currentNode ->next;
    }
    //If all neighbors have been visited and DFS was not able to find the destination, we will return 0 <-backtrack
    return 0;
}


int* city_population (int N, int* population, int** road, int Q, int** cities) 
{
    //sanity check
    if (N == 0 || population == NULL || road == NULL || cities == NULL)
        return NULL;
    
    int i , j; // for loop counters
    int u , v; // u <- src , v <- desti
    int count, *visited , *queryAnswer; 

    ListNode *newNodeU, *newNodeV ;
    ListNode **adjList;

    //visited array intiailization
    visited = (int *)calloc(N , sizeof(int));

    //queryAnswer array intiailization <- final output
    queryAnswer = (int *)calloc(Q , sizeof(int));

    //adjList initialization
    adjList = (ListNode **)malloc(N * sizeof(ListNode *));

    for(i = 0; i < N; i++)
    {
        adjList[i] = NULL;
    }

    //adjacency matrix -> adjacency list (adding edges)
    for(i = 0; i < N - 1 ; i++)
    {   
        u = road[i][0]; //source
        v = road[i][1]; //destination

        newNodeU = (ListNode *)malloc(sizeof(ListNode));
        newNodeV = (ListNode *)malloc(sizeof(ListNode));
        
        //since this is undirected graph -> we have add the newNode to both source & destination linked list
        //we add the newNode to the front of the list rather than the back
        newNodeU->city_ID = v;
        newNodeU->next = adjList[u - 1];
        adjList[u - 1] = newNodeU;

        newNodeV->city_ID = u; 
        newNodeV->next = adjList[v - 1];
        adjList[v - 1] = newNodeV;
    }
    //adjacencyList(adjList, N);
    
    //Traverse the query array to access U (starting point) , V (ending point), W (max. population)
    for(i = 0; i < Q; i++)
    {   
        //we re-intiailize the various trackers/counters
        count = 0;

        for(j = 0; j < N; j++)
        {
            visited[j] = 0;              
        }
        
        DFS(adjList , cities[i][0] , cities[i][1] , cities[i][2] , population , &count , visited);
        //we will update count into the corresponding queryAnswer index
        queryAnswer[i] = count;

    }

    //free visited & adjList arrays
    free(visited);

    for(i = 0; i < N; i++)
    {
        free(adjList[i]);
    } 

    free(adjList);
    return queryAnswer;
}

//this is just to checking our adjacency list
void adjacencyList(ListNode **adjList, int N)
{
    int i;
    ListNode *currentNode;

    for(i = 1; i <= N; i++)
    {
        currentNode = adjList[i - 1];

        printf("%d:",i);
        while(currentNode != NULL)
        {
            printf("%d->", currentNode->city_ID);
            currentNode = currentNode->next;
        }
        printf("\n");
    }
}