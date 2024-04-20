#include <stdio.h>
#include <stdlib.h>

//memory
int *r;

int max(int a, int b)
{
    if (a>b) return a;
    return b;
}

// int cr_bottom_up_dp_print_recurse(int *p, int n, int *map)
// {
//     // base case
//     if (n==0)
//         return 0;
//     if (map[n] != -1)
//         return map[n];
//     int maximum = -1;
//     for(int i=1; i<=n; i++)
//     {
//         int price = p[i] + cr_bottom_up_dp_print_recurse(p,n-i,map);
//         maximum = max(maximum, price);
//         map[n] = maximum;
//     }
//     printf("%d\n", maximum);
//     return maximum;
// }

// int cr_bottom_up_dp_print(int *p, int n)
// {
//     //write your code here
//     int *map = (int*) malloc(sizeof(int)*(n+1));
//     for (int i=0; i<=n; i++)
//     {
//         map[i] = -1;
//     }
//     return cr_bottom_up_dp_print_recurse(p,n,map);
// }

int cr_bottom_up_dp_print(int *p, int n)
{
    int map[n+1];
    for (int i=0; i<n+1; i++)
        map[i] = 0;
    for (int l=1; l<n; l++)
    {
        int max_val = -1;
        for (int cut=1; cut<l; cut ++)
        {
            int new_val = p[cut] + map[l-cut];
            max_val = max(new_val, max_val);
        }
        map[l] = max_val;
    }
    return map[n];
}

 
void main ()
{
    int n;      //length of  rod
    int function;
    int i;
    int *p;     //price list
    
    int price_list[10] = {0,1,4,8,9,10,17,17,20,24}; //declare one more value to cover the index 0;
    
    n = sizeof(price_list) / sizeof(int) - 1;
    p = price_list;
    
    
    //allocate the memory array
    r = malloc(sizeof(int) * (n+1));
    
    
    //set all memory elements to -1
    for (i=0; i<=n; i++)
        r[i] = -1;
                
    printf("The maximun value is: %d \n", cr_bottom_up_dp_print(p,n));
}