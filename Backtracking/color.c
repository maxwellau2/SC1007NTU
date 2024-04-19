#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int count = 0; // count the number of solutions
int V; //number of regions

/* A utility function to print solution */
void printSolution(int* color)
{
    printf(
        "Solution Exists:"
        " Following are the assigned colors \n");
    for (int i = 0; i < V; i++)
        printf(" %d ", color[i]);
    printf("\n");
}
 
/* A utility function to check if
   the current color assignment
   is safe for vertex v i.e. checks
   whether the edge exists or not
   (i.e, graph[v][i]==1). If exist
   then checks whether the color to
   be filled in the new vertex(c is
   sent in the parameter) is already
   used by its adjacent
   vertices(i-->adj vertices) or
   not (i.e, color[i]==c) */
int isSafe(
    int v, int** graph,
    int* color, int c)
{
    for (int i = 0; i < V; i++)
        if (graph[v][i] && c == color[i])
            return 0;
    return 1;
}
 
/* A backtracking function
to solve m coloring problem */
// int graphColoring(
//     int** graph, int m,
//     int* color, int v)
// {
//     //write your code here
//     if (v==V) // if current vertex is the last one
//     {
//         count ++;
//         printSolution(color);
//         return 0;
//     }
//     for (int i=1; i<m+1; i++) // for each color possible
//     {
//         if (isSafe(v,graph,color,i)) // if the color is safe to use
//         {
//             color[v] = i; // color it
//             // recursively call for the next vertex
//             graphColoring(graph,m,color,v+1);
//             // undo the color assignment to explore other colors
//             color[v] = 0;
//         }
//     }
//     // return count;
//     return count;
// }


int graphColoring(int** graph, int m, int* color, int v)
    {
        // base case, v=V
        if (v==V)
        {
            printSolution(color);
            return 1;
        }
        // else, look thru other colors in this vertex, check if its safe
        int result = 0;
        for (int i=1; i<=m; i++)
        {
            if (isSafe(v,graph, color,i))
            {
                // color it
                color[v] = i;
                result = graphColoring(graph, m, color, v+1) + result;
                // backtracking step
                color[v] = 0;
            }
        }
        return result;
    }

int main()
{
    // testGraphColoring();
    int m;
    int **graph;
    int *color;
    
    printf("Enter number of colors:\n");
    scanf("%d",&m);
    
    printf("Enter number of regions:\n");
    scanf("%d",&V);
    
    int i,j;
    color = (int *) malloc(V*sizeof(int));
    graph = (int **) malloc(V*sizeof(int *));
    
    for (i=0;i<V;i++)
        graph[i] = (int *) malloc(V*sizeof(int));
    
    printf("Input the adjacency matrix:\n");
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
             scanf("%d",&graph[i][j]);
    
 
    // Initialize all color values as 0.
    for (i = 0; i < V; i++)
        color[i] = 0;
 
    int sol = graphColoring(graph, m, color, 0);
        
    printf("There is/are total %d solution(s)", sol);
    return 0;
}

