#include <stdio.h>
#include <stdlib.h>

int nQueens(int** board, int N, int col);
int isSafe(int** board,int N, int row, int col);
void printSolution(int** board, int N);

int main()
{
    int **board;
    int BSize;

    int i,j;

    printf("Enter the size of chessBoard:\n");
    scanf("%d",&BSize);

    board = (int **)malloc(BSize*sizeof(int *));
    for(i=0;i<BSize;i++)
        board[i] = (int *)malloc(BSize*sizeof(int));

    for(i=0;i<BSize;i++)
       for(j=0;j<BSize;j++)
           board[i][j] = 0;

    nQueens(board, BSize, 0);
    printSolution(board, BSize);
    system("pause");
    return 0;
}

int nQueens(int** board, int BSize, int col)// COLUMN 0
{
    if(col == BSize){
        //printSolution(board, BSize);
        return 1;
    }

    //we just need to loop through rows
    for(int i = 0; i < BSize ; i++){
        //check if we can put any queen in any of the rows
        if(isSafe(board,BSize,i,col))
        {   
            board[i][col] = 1; //CHOICE
            //we move to the next col and do the same thing 
            nQueens(board,BSize,col+1);
            //base case is if we cannot find a place to put, we undo what we did
            board[i][col] = 0;
        } 

    }
    //we could not find any rows
    return 0;
}             
  

//Safe checking
int isSafe(int** board,int BSize, int row, int col)
{
    int i, j;

    // Horicatal check
    for (i = 0; i < col; i++)
        if (board[row][i])
            return 0;

    // Upper left diagonal check
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return 0;

    // Lower left diagonal check
    for (i = row, j = col; j >= 0 && i < BSize; i++, j--)
        if (board[i][j])
            return 0;

    return 1;
}

void printSolution(int** board, int BSize)
{
    int i,j;
    for (i = 0; i < BSize; i++) {
        for (j = 0; j < BSize; j++){
            if(board[i][j]==1)
                printf(" Q ");
            else
                printf(" + ");
        }
        printf("\n");
    }
    printf("\n");
}
