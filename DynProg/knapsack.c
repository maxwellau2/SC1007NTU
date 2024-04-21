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
    // establish base cases
    // we've seen this guy b4
    if (map[i][j] >=0)
        return map[i][j];
    // j negative
    if (j < 0)
        return map[i][j];
    // subproblem only has 1 column
    if (i==1)
    {
        // capacity greater than size
        if (j >= s[i])
            map[i][j] = s[i];
        // capcity less than size
        else
            map[i][j] = 0;
        return map[i][j];
    }
    // subproblem has more than 1 column
    // case 1. capacity greater than size
    if (j >= s[i])
        map[i][j] = max(knapsack(i-1,s,v,j,map), knapsack(i-1,s,v,j-s[i],map) + v[i]);
    else // case 2. capacity less than size
        map[i][j] = knapsack(i-1,s,v,j,map);
    return map[i][j];
}



// {
//     // establish base cases
//     // case 1, we've seen this guy b4
//     if (map[i][j] >= 0)
//         return map[i][j];
//     // case 2, j < 0,
//     if (j<0)
//         return 0;
//     // case 3, subproblem only has 1 column
//     if (i == 1)
//     {
//         // capacity > size
//         if (j >= s[i])
//             map[i][j] = s[i];
//         else // cap < sz
//             map[i][j] = 0;
//         return map[i][j];
//     }
//     // subproblem has more than 1 column
//     // case 1. capacity is larger than size, can CHOOSE to include/exlcude
//     if (j >= s[i])
//         map[i][j] = max(knapsack(i-1,s,v,j,map), knapsack(i-1,s,v,j-s[i], map) + v[i]);
//     else // case 2. bopes need to exclude, run it back
//         map[i][j] = knapsack(i-1,s,v,j,map);
//     return map[i][j];
// }

// {
//     // establish base cases
//     // case 1: we've seen this guy b4
//     if (map[i][j] >= 0)
//         return map[i][j];
//     // case 2, j negative, 
//     if (j < 0)
//         return 0;
//     // case 3, subproblem only has 1 column
//     if (i==1)
//     {
//         // capacity greater than size
//         if(j >= s[i])
//             map[i][j] = s[i];
//         // capacity smaller than size
//         else
//             map[i][j] = 0;
//         return map[i][j];
//     }
//     // case 4, subproblem has multiple columns
//     if (j < s[i]) // capacity less than size
//         map[i][j] = knapsack(i-1, s, v, j, map);
//     else // capacity greater than size, get max(include weight, not include weight)
//         map[i][j] = max(knapsack(i-1,s,v,j,map), knapsack(i-1,s,v,j-s[i],map) + v[i]);

//     return map[i][j];
// }




// {
//     if (map[i][j] >= 0)
//         return map[i][j];
//     if (j<=0)
//         return 0;
//     // reach the first column
//     if (i==1)
//     {
//         if(s[i] > j) // size is bigger than max capacity
//             map[i][j] = 0;
//         else
//             map[i][j] = v[i];
//         return map[i][j];
//     }
//     // subproblem has more than 1 column
//     if (j-s[i] < 0) // capacity < size
//         map[i][j] = knapsack(i-1, s, v, j, map);
//     else
//         map[i][j] = max(knapsack(i-1,s,v,j,map), knapsack(i-1,s,v,j-s[i],map) + v[i]);
//     return map[i][j];
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