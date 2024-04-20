#include <stdio.h>
#include <stdlib.h>

//memory
int *r;

int cr_recursive(int *p, int n)
{
    // write your code here
    // base case, no more rod
    if (n==0)
        return 0;
    int max = -1;
    for (int i=1; i<=n; i++)
    {
        int price = p[i] + cr_recursive(p, n-i);
        if (price > max)
            max = price;
    }
    return max;
}

int cr_top_down_dp_recurse(int* p, int n, int map[])
{
    if (n==0)
        return 0;
    if (map[n] != -1)
        return map[n];
    // bopes need to recurse
    int max = -1;
    for (int i=1; i<=n; i++)
    {
        int price = p[i] + cr_top_down_dp_recurse(p, n-i, map);
        if (price > max)
        {
            max = price;
            map[n] = max;
        }
    }
    return max;
}
int cr_top_down_dp(int *p, int n)
{
    //write your code here
    int map[n+1];
    for(int i=0; i<n+1; i++)
        map[i] = -1;
    int res = cr_top_down_dp_recurse(p,n,map);
    return res;
}

int cr_bottom_up_dp(int *p, int n)
{
    //write your code here
    int map[n+1];
    for (int i=0; i<n+1; i++)
        map[i] = -1;

    for(int i=1; i<n+1; i++)
    {
        for(int j=1; j<i; j++)
        {
            
        }
    }
}
 
void main ()
{
    int n;      //length of  rod
    int function;
    int i;
    int *p;     //price list
    
    int price_list[10] = {0,1,5,8,9,10,17,17,20,24}; //declare one more value to cover the index 0;
    
    n = sizeof(price_list) / sizeof(int) - 1;
    p = price_list;
    
    
    //allocate the memory array
    r = malloc(sizeof(int) * (n+1));
    
    printf("Choose a function (1 for recursive, 2 for top-down DP, 3 for bottom-up DP, 0 to stop): \n");
    scanf("%d",&function);
    while (function != 0)
    {
        if (function == 1)
        {
            printf("The maximun value is: %d \n", cr_recursive(p,n));
        }
        else if (function == 2)
        {
            //set all memory elements to -1
            for (i=0; i<=n; i++)
                r[i] = -1;
                
            printf("The maximun value is: %d \n", cr_top_down_dp(p,n));
        }
        else if (function == 3)
        {
            //set all memory elements to -1
            for (i=0; i<=n; i++)
                r[i] = -1;
                
            printf("The maximun value is: %d \n", cr_bottom_up_dp(p,n));
        }
        printf("Choose a function (1 for recursive, 2 for top-down DP, 3 for bottom-up DP, 0 to stop): \n");
        scanf("%d",&function);
    }
}