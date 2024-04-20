# Notes for backtracking

### Some of the patterns we can follow is the following template

1. Establish a base case (usually, if all is safe, return 1)
2. Usually ur gonna wanna do some sort of draft on pen n paper to figure out a brute force solution
3. Once you've identified what the brute force solution is, think about how you wanna implement the isSafe() function
4. So far, nQueens, color all follow this specific problem

``` python
def backtrack(states, moves)
    if base_case:
        return 1
    else:
        // visit all possible outcomes
        solutions = 0
        for i in possible_moves:
            if isSafe(i):
                place the thing
                solution += backtrack_recursive(states, moves+1)
                remove the thing
    return solutions
```
### nQueens Problem 
``` c
int nQueens(int** board, int BSize, int col)
{
    int solutions = nQueenRecurse(board, BSize, 0);
    printf("%d", solutions);
}

int nQueenRecurse(int**board, int BSize, int col)
{
    // base case, all 4 queens are on the board
    if (col == BSize)
    {
        printSolution(board, BSize);
        return 1;
    }
    // else iterate thru all possible moves
    int solutions = 0;
    for (int i=0; i<BSize; i++)
    {
        if (isSafe(board, BSize, i, col))
        {
            // place queen
            board[i][col] = 1;
            // recurse
            solutions += nQueenRecurse(board, BSize, col+1);
            // backtracking step, remove queen form board to explore other solutions
            board[i][col] = 0;
        }
    }
    return solutions;
}
```

### Graph coloring problem
```c
int graphColoring(int** graph, int m, int* color, int v)
{
    // base case: all vertices colored, global variable V is the number of vertices
    if (v == V)
    {
        printSolution(color);
        return 1;
    }
    int solutions = 0;
    // iterate all other colors for this vertex, color is defined by m
    for (int i=1; i<=m; i++)
    {
        // check if move is valid
        if(isSafe(v, graph, color, i))
        {
            // color the graph
            color[v] = i;
            // look for other solutions for the NEXT vertex (v+1)
            solutions += graphColoring(graph, m, color, v+1);
            // backtracking step, uncolor it
            color[v] = 0;
        }
    }
    return solutions;
}
```
paste this txt to see solution
``` txt
3
4
0 1 1 1
1 0 1 0
1 1 0 1
1 0 1 0
```
output
```
Enter number of colors:
3 
Enter number of regions:
4
Input the adjacency matrix:
0 1 1 1
1 0 1 0
1 1 0 1
1 0 1 0
Solution Exists: Following are the assigned colors 
 1  2  3  2 
Solution Exists: Following are the assigned colors 
 1  3  2  3
Solution Exists: Following are the assigned colors
 2  1  3  1
Solution Exists: Following are the assigned colors
 2  3  1  3
Solution Exists: Following are the assigned colors
 3  1  2  1 
Solution Exists: Following are the assigned colors
 3  2  1  2
There is/are total 6 solution(s)
```