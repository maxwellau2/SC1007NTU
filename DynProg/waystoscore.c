#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    if (a>b) return a;
    return b;
}

int waysToScore_recurse(int n, int* score, int* map)
{
    // base case 1, remaining score negative
    if (n<0)
        return 0;
    // base case 2, remaining score is exactly 0, solution found
    if (n==0)
        return 1;
    // check map
    if (map[n] != -1)
        return map[n];

    int solutions = 0;
    for (int i=0; i<3; i++)
    {
        int remaining = n - score[i];
        solutions += waysToScore_recurse(remaining, score, map);
    }
    map[n] = solutions;
    return solutions;
}


int waysToScore(int n, int* score)
{
    //write your code here
    // create memo table
    int *map = (int*)malloc(sizeof(int)*n+1);
    for (int i=0; i<n+1; i++)
    {
        map[i] = -1;
    }
    return waysToScore_recurse(n,score,map);
}

 
void main ()
{
    int n;

    int score[3] = {3,5,10}; 

    printf("Enter the value of N: ");
    scanf("%d",&n);


    printf("The number of ways to reach to a score of %d is: %d \n",n, waysToScore(n,score));
}
