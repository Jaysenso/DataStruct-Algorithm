#include <stdio.h>
#include <stdlib.h>

void dualSearch (int[],int, int, int[]);

int main()
{
    int i,size,K;
    int* A;
    int index[2] = {-1,-1};

    //Search key
    printf("Enter K value: ");
    scanf("%d",&K);

    //create an array   
    printf("Insert Array size: ");
    scanf("%d",&size);
    A=(int *)malloc(sizeof(int)*size);
    printf("Insert Array element: ");
    for(i=0; i<size; i++)
    {
        scanf("%d",&A[i]);
    }

    dualSearch(A,size,K,index);

    if(index[0]!=-1)
        printf("%d %d\n",index[0], index[1]);
    else
        printf("Not found");

    free(A);
    
    return 0;
    system("pause");
}
/*
ALGORITHM EXPLANATION:--------------------------------------------------------------
1. we will use double pointers to search through the trees
2. we add both elements that the pointers are pointing and compare it to k
3. if its sum of both elements == k , we will move both elements into our dualIndex
4. we will then return to main function and print content of DualIndex

*/

void dualSearch(int A[], int size, int K, int dualIndex[])
{
    if (A == NULL || size == 0)
        return;

    int i, j;
    int  sum;

    for(i = 0; i < size ;i++)
    {
        for(j = i + 1 ; j < size - i; j++)
        {
            sum = A[i] + A[j];
            if (sum == K)
                {
                    dualIndex[0] = A[i];
                    dualIndex[1] = A[j];
                    break;
                }
        }
    }
}
