#include <stdio.h>
#include <stdlib.h>

//memory
int *r;

int max(int a, int b)
{
    if (a>b) return a;
    return b;
}

int cr_recursive(int *p, int n)
{
    // base case no more rod left
    if (n == 0)
        return 0;
    // look for other rod lengths
    int maxval = -1;
    for (int i=1; i<=n; i++)
    {
        int price = p[i] + cr_recursive(p, n-i); // get new price,
        // intuition is to get the current price, and find max value of REMAINING rod
        maxval = max(price, maxval);
        // update max val
    }
    return maxval;
}

int cr_top_down_dp_recurse(int* p, int n, int map[])
{
    // base case
    if (n==0)
        return 0;

    // we've seen this guy before ! (memoization)
    if (map[n] != -1)
        return map[n];

    // look for prices of remaining rod
    int maximum = -1;
    for (int i=1; i<=n; i++)
    {
        int price = p[i] + cr_top_down_dp_recurse(p,n-i,map);
        maximum = max(price, maximum);
        map[n] = maximum;
    }
    return maximum;
}


int cr_top_down_dp(int *p, int n)
{
    // init map
    int *map = (int*)malloc(sizeof(int)*n+1);
    for (int i=0; i<=n; i++)
    {
        map[i] = -1; // init values to -1
    }
    // call recursive step
    return cr_top_down_dp_recurse(p, n, map);
}

int cr_bottom_up_dp(int *p, int n)
{
    //write your code here
    // create map of size n, initialise to 0 to store possible lengths
    int map[n+1];
    for (int i=0; i<n+1; i++)
        map[i] = 0;

    // for each length from 1 to n
    for (int length = 1; length < n+1; length ++)
    {
        int max_val = -1;
        // number of possible cuts is the length (u cut the length into 1cm chunks, u get length number of items), iterate over them
        for (int cut = 1; cut < length+1; cut ++)
        {
            // get maximum possible value
            int price = p[cut] + map[length-cut];
            max_val = max(max_val, price);
        }
        map[length] = max_val; // store in map
    }
    return map[n];
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