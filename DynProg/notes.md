## Dynamic Programming

### 2 Approaches
1. Top Down (Memoization)
2. Bottom Up (Tabulation)

* Memoization is about storing states that have been previously, so as to not take up so much time
* Tabularization is to establish all base cases in a table to build the solution from the ground up

I ain't even gonna lie, I find the **top down** approach far more intuitive. However, the bottom up approach is far easier to understand once you draw it out.

### Patterns in DP
1. How to store previous states?
2. What are some of the base cases involved?
3. How how does the current state relate to the next state?

Here's some pseudocode
```python
def dp_ex(state, memo):
    # we've seen this motherfucker b4
    if (memo[state] != -1):
        return memo[state]

    if (state == BASE_CASE):
        return BASE_CASE_VAL

    # otherwise, bobian need to recurse :(
    memo[state] = dp_ex(state-1, memo)

    return memo[state]
```

The shown pseudocode is an example of an application of memoization to DP. Elements include

1. checking memory table, have we seen the state before?
2. establishing base cases
3. storing unseen state into memo using recursive call.
4. return of memo at state
   
# Below is some example questions to think about

## Rod cutting problem
* Pure Recusive Solution
``` c
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
```

* Recursion with Memoization
``` c
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
```
Bottom up approach fo rod cutting, the ONLY question i know how to solve bottom up LOLOL
``` c
int cr_bottom_up_dp(int *p, int n)
{
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
```

## Fib Sequence
``` c
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
```

## Ways to score (tutorial qn)
``` c
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
```

## 0/1 Knapsack problem
``` c
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
```

Appendix
I created a simple helper function on the side to help code a lil easier
```c
int max(int a, int b)
{
    if (a>b) return a;
    return b;
}
```