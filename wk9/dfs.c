#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graph{
    int V;
    int E;
    int *visited; //store the visited vertices
    int **matrix;
}Graph;

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} Stack;

// You should not change the prototypes of these functions
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
////GRAPH////////////////////////////////////////////
void printGraphMatrix(Graph );
void dfs(Graph* g, int start);
void view_visited(Graph g);
////////////////////////////////////////////

int Connected (Graph);

int main()
{
    Graph g;
    int i,j;
    

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.matrix[i] = (int *)malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++)
       for(j=0;j<g.V;j++)
           g.matrix[i][j] = 0;
	
	g.visited = (int *) malloc(sizeof(int)*g.V);
    for(i=0;i<g.V;i++) g.visited[i] = 0;
    
    
    int V1, V2;
    printf("Enter a directed edge: (press a to stop)\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.matrix[V1-1][V2-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter a directed edge: (press a to stop)\n");
    }
    scanf("%*c");
    
    
    int res = Connected(g);
    if(res == 1)
        printf("The graph is strongly connected.\n");
    else
        printf("The graph is not strongly connected.\n");

    return 0;
}

int Connected(Graph g)
{
    // printGraphMatrix(g);
    // perform DFS from every vertex
    for (int i = 0; i < g.V; i++)
    {
        dfs(&g, i);
        view_visited(g);
        // check if all nodes are visited
        for (int j = 0; j < g.V; j++)
        {
            if (!g.visited[j])
                return 0; // if any vertex is not visited, return 0
        }
    }
    return 1; // if all vertices are visited from every starting vertex, return 1
}

void dfs(Graph* g, int start)
{
    // create stack
    Stack s;
    int found_unvisited;
    s.head = NULL;
    s.size = 0;
    for (int i=0; i<g->V; i++) //reset visited arr to 0
    {
        g->visited[i] = 0;
    }
    push(&s, start);
    g->visited[start] = 1;
    while (!isEmptyStack(s))
    {
        found_unvisited = 0;
        int current_vertex = peek(s);
        // visit neighbours of current vertex
        for (int i=0; i < g->V; i++)
        {
            int neighbour = i;
            if (g->matrix[current_vertex][i] != 0 && g->visited[neighbour] == 0) // they are adjacent and the neighbour has yet to be visited
            {
                push(&s, neighbour);
                g->visited[neighbour] = 1;
                found_unvisited = 1;
                break;
            }
        }
        if (!found_unvisited)
        {
            pop(&s);
        }
    }
}


void view_visited(Graph g)
{
    printf("Visited:\n");
    for (int k=0; k<g.V; k++)
    {
        printf("idx %d : %d\n", k, g.visited[k]);
    }
}

void printGraphMatrix(Graph g)
{
    int i,j;

    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.matrix[i][j]);
        printf("\n");
    }

}

void push(Stack *sPtr, int vertex)
{
	StackNode *newNode;
    newNode= malloc(sizeof(StackNode));
    newNode->vertex = vertex;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if(sPtr==NULL || sPtr->head==NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

int isEmptyStack(Stack s)
{
     if(s.size==0) return 1;
     else return 0;
}

int peek(Stack s){
    return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
	while(pop(sPtr));
}
