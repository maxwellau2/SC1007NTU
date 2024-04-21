#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;

typedef struct _graph{
    int V;
    int E;
    int *visited;
    int **matrix;
}Graph;

typedef ListNode QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

int SD (Graph G, int v, int w);

void printGraphMatrix(Graph );

// You should not change the prototypes of these functions
void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);

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
    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.matrix[V1-1][V2-1] = 1;
            g.matrix[V2-1][V1-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other: (press a to stop)\n");
    }
    scanf("%*c");
    // printGraphMatrix(g);
    
    printf("Enter two vertices for finding their shortest distance: (press a to stop)\n");
    scanf("%d %d", &i, &j);

    int d = SD(g,i,j);
    if(d==-1)
        printf("%d and %d are unconnected.\n",i,j);
    else
        printf("The shortest distance is %d\n",d);
    return 0;
}

int hasVisited(int arr[], int node, int size)
{
    for (int i=0; i<size; i++)
    {
        if (arr[i] == node)
            return 1;
    }
    return 0;
}

int SD(Graph g, int v, int z)
{
    // just an application of bfs, visited table stores nonzero distances
    Queue q;
    q.head=NULL;
    q.tail=NULL;
    q.size=0;
    //enq
    enqueue(&q, v-1);
    // set all nonvisited to -1
    for (int i=0; i<g.V; i++)
        g.visited[i] = -1;
    g.visited[v-1]=0;
    while(!isEmptyQueue(q))
    {
        int current_node = dequeue(&q);
        printf("%d ", current_node+1);
        if (current_node == z-1)
            return g.visited[current_node];
        // visited neighbours;
        for (int i=0; i<g.V; i++)
        {
            if(g.matrix[current_node][i] && (g.visited[i]==-1))
            {
                g.visited[i] = g.visited[current_node] + 1;
                enqueue(&q, i);
            }
        }
    }
    return -1;
}















// {
//     // printGraphMatrix(g);
//     Queue q;
//     q.head = NULL;
//     q.tail = NULL;
//     q.size =  0;
//     // en-q the start
//     enqueue(&q, v-1);
//     // set start-start distance to 0
//     g.visited[v-1] = 0;
//     // perform bfs traversal
//     while (!isEmptyQueue(q))
//     {
//         int current_vertex = dequeue(&q);
//         if (current_vertex == z-1)
//             return g.visited[z-1];
//         // visit neighbours of current vertex
//         for (int i=0; i < g.V; i++)
//         {
//             if (g.matrix[current_vertex][i] != 0) // they are adjacent
//             {
//                 int neighbour = i;
//                 if (g.visited[neighbour] == 0)
//                 {
//                     g.visited[neighbour] = g.visited[current_vertex] + 1;
//                     enqueue(&q, neighbour);
//                     // printf("%d \n", neighbour);
//                 }
//             }
//         }
//     }
//     return -1;
// }

void printGraphMatrix(Graph g)
{
    int i,j;

    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.matrix[i][j]);
        printf("\n");
    }

}


void enqueue(Queue *qPtr, int item) {
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = item;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr) {
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       int headValue = qPtr->head->vertex;
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return headValue;
    }
}

int getFront(Queue q){
    return q.head->vertex;
}

int isEmptyQueue(Queue q) {
    if(q.size==0) return 1;
    else return 0;
}

void removeAllItemsFromQueue(Queue *qPtr)
{
	while(dequeue(qPtr));
}