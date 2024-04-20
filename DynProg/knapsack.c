#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

int knapsack(int i, int *s, int *v, int j, int **map)
{
    
}
// {
//     // if the map value is greater than zero, return the value itself (memoization part)
//     if (map[i][j] >= 0)
//         return map[i][j];

//     if(j<=0) // else return
//         return 0;

//     if (i==1) // subproblem only has 1 column (1 item)
//     {
//         if (s[i] <= j) // if size less than capacity
//         {
//             map[i][j] = v[i]; // place weight in bag map
//             return v[i]; // return for future comparison, seen in end part of fn
//         }
//         else
//         {
//             map[i][j] = 0; // it's too big step bro, dont put it in
//             return 0;
//         }
//     }
//     else
//     {
//         if(j-s[i] < 0) // subproblem has more than 1 column, if the capacity greater than size
//         {
//             map[i][j] = knapsack(i-1, s, v, j, map); // fill in the map
//             return map[i][j]; // for future comparison
//         }
//         else
//         {
//             // compare previous row's value, and current row's potential max value (rejected if exceeds capacity)
//             map[i][j] = max(knapsack(i-1, s, v, j, map), knapsack(i-1, s, v, j-s[i], map) + v[i]);
//             return map[i][j]; // return for future reference
//         }
//     }
// }

int bottom_up_dp(int n, int *s, int *v, int C)
{
    //write your code here
    // create 2d map based
    int **map = (int **)malloc(sizeof(int *) * (n + 1));
    for (int i = 0; i <= n; i++) 
    {
        map[i] = (int *)malloc(sizeof(int) * (C + 1));
        for (int j = 0; j <= C; j++) 
        {
            map[i][j] = -1;
        }
    }
    // call knapsack
    int res = knapsack(n, s, v, C, map);
    return res;
}

 
int main ()
{
    int n,C;
    int function;
    int *s;
    int *v;
    int i,j;
    printf("Enter the number of items n:\n");
    scanf("%d",&n);
    printf("Enter the capacity C:\n");
    scanf("%d",&C);
    s = (int *) malloc(sizeof(int) * (n+1));
    v = (int *) malloc(sizeof(int) * (n+1));
    
    printf("Enter the sizes of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&s[i]);
        
    printf("Enter the values of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&v[i]);
    
    printf("The maximum value is: %d \n", bottom_up_dp(n,s,v,C));
        
}