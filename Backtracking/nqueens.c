#include <stdio.h>
#include <stdlib.h>

int nQueens(int** board, int N, int col);
int isSafe(int** board,int N, int row, int col);
void printSolution(int** board, int N);
int nQueenRecurse(int**board, int BSize, int col);

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

    return 0;
}

int nQueens(int** board, int BSize, int col)
{
 //Write your code here
 //Safe Place checking is provide below, you are free to use it.
    nQueenRecurse(board, BSize, 0);
    return 1;
}

int nQueenRecurse(int**board, int BSize, int col)
{
    // base case : all queens have been placed
    if (col == BSize)
    {
        // all queens on board, print
        printSolution(board, BSize);
        return 1;
    }
    // look thru current ROWS of column and check if queens are safe
    int res = 0;
    for (int i=0; i<BSize; i++)
    {
        if (isSafe(board, BSize, i, col))
        {
            board[i][col] = 1;
            res = nQueenRecurse(board, BSize, col + 1) || res;
            // backtrack
            board[i][col] = 0;
        }
    }
    return res;
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
