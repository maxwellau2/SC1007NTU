#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int recurse(int k, int *map);

int recurse(int k, int *map)
{
    // trivial base cases
    if (k==0)
        return 0;
    if (k==1)
        return 1;
    if (k==2)
        return 2;
    // if map not filled before, compute the LRR manually
    if (map[k] == -1)
        map[k] = recurse(k-1,map) + 2*recurse(k-2,map) - 3*recurse(k-3,map); // fill the map
    return map[k];
}

int top_down_dp(int n)
{
    //write your code here
    int map[n+1];
    // clear map
    for(int i=0; i<n+1; i++)
    {
        map[i] = -1;
    }
    map[0] = 0;
    map[1] = 1;
    map[2] = 2;
    int res = recurse(n, map);
    return res;
}
 
int main ()
{
    int n;
    int function;
    int i;
    printf("Enter the value of n:\n");
    scanf("%d",&n);
    
    printf("The value of F(%d) is: %d \n", n, top_down_dp(n));
        
}