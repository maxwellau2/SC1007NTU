///////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//////////////////inked list ///////////

typedef struct _listnode{
   int item;
   struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
   ListNode *tail;
} LinkedList;

///////////////// stack    /////////////////

typedef struct stack{
	LinkedList ll;
} Stack;

/////////////// queue /////////////////////

typedef struct _queue{
	LinkedList ll;
} Queue;

////////// function prototypes /////////////

// You should not change the prototypes of these functions

void interleaveQueue(Queue *q);

////////////////////////////////////////////

void push(Stack *s, int item);
int pop(Stack *s);
int peek(Stack *s);
int isEmptyStack(Stack *s);

void enqueue(Queue *q, int item);
int dequeue(Queue *q);
int isEmptyQueue(Queue *s);

///////////////////////////////////////////////////////
void printList(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);
void removeAllItems(LinkedList *ll);

////////////////////////////////////////////////////////


int main() {
    // Test Case 1: Interleaving an empty queue
    printf("Test Case 1: Interleaving an empty queue\n");
    Queue emptyQueue;
    emptyQueue.ll.head = NULL;
    emptyQueue.ll.tail = NULL;
    emptyQueue.ll.size = 0;
    printf("Original queue: ");
    printList(&(emptyQueue.ll));
    interleaveQueue(&emptyQueue);
    printf("Interleaved queue: ");
    printList(&(emptyQueue.ll));
    removeAllItems(&(emptyQueue.ll));
    printf("\n");

    // Test Case 2: Interleaving a queue with one element
    printf("Test Case 2: Interleaving a queue with one element\n");
    Queue singleQueue;
    singleQueue.ll.head = NULL;
    singleQueue.ll.tail = NULL;
    singleQueue.ll.size = 0;
    enqueue(&singleQueue, 1);
    printf("Original queue: ");
    printList(&(singleQueue.ll));
    interleaveQueue(&singleQueue);
    printf("Interleaved queue: ");
    printList(&(singleQueue.ll));
    removeAllItems(&(singleQueue.ll));
    printf("\n");

    // Test Case 3: Interleaving a queue with even number of elements
    printf("Test Case 3: Interleaving a queue with even number of elements\n");
    Queue evenQueue;
    evenQueue.ll.head = NULL;
    evenQueue.ll.tail = NULL;
    evenQueue.ll.size = 0;
    for (int i = 1; i <= 6; i++)
        enqueue(&evenQueue, i);
    printf("Original queue: ");
    printList(&(evenQueue.ll));
    interleaveQueue(&evenQueue);
    printf("Interleaved queue: ");
    printList(&(evenQueue.ll));
    removeAllItems(&(evenQueue.ll));
    printf("\n");

    // Test Case 4: Interleaving a queue with odd number of elements
    printf("Test Case 4: Interleaving a queue with odd number of elements\n");
    Queue oddQueue;
    oddQueue.ll.head = NULL;
    oddQueue.ll.tail = NULL;
    oddQueue.ll.size = 0;
    for (int i = 1; i <= 5; i++)
        enqueue(&oddQueue, i);
    printf("Original queue: ");
    printList(&(oddQueue.ll));
    interleaveQueue(&oddQueue);
    printf("Interleaved queue: ");
    printList(&(oddQueue.ll));
    removeAllItems(&(oddQueue.ll));
    printf("\n");

    return 0;
}

////////////////////////////////////////////////////////////

// void interleaveQueue(Queue *q)
// {
//     Stack stack;
//     int halfsize = q->ll.size /2;
//     // push first half elements onto the stack
//     for (int i=0; i < halfsize; i++)
//     {
//         push(&stack, dequeue(q));
//     }
//     // enqueue back the stack elements
//     while(!isEmptyStack(&stack))
//     {
//         enqueue(q, pop(&stack));
        
//         printf("HIII\n");
//         if(isEmptyStack(&stack)) break;
//     }
    
//         printf("HIII\n");
//     // dequeue the first half elements of q, then enque them back
//     for(int i=0; i<halfsize; i++)
//     {
//         enqueue(q, dequeue(q));
//     }
//     // push the first half elements into the stack
//     for (int i=0; i<halfsize; i++)
//     {
//         push(&stack, dequeue(q));
//     }
//     while(!isEmptyStack(&stack))
//     {
//         enqueue(q, pop(&stack));
//         enqueue(q, dequeue(q));
//     }
// }

void interleaveQueue(Queue *q)
{
    Stack s;
    s.ll.head = NULL;
    s.ll.size = 0;
    s.ll.tail = NULL;
    int size = q->ll.size;
    int halfsize = size/2;
    for (int i=0; i<halfsize; i++)
    {
        push(&s, dequeue(q));
    }
    for (int i=0; i<halfsize; i++)
    {
        enqueue(q, pop(&s));
    }
    for(int i=0; i<halfsize; i++)
    {
        enqueue(q, dequeue(q));
    }
    for (int i=0; i<halfsize; i++)
    {
        push(&s, dequeue(q));
    }
    
    for(int i=0; i < halfsize; i++)
    {
         enqueue(q, pop(&s));
         enqueue(q, dequeue(q));
    }
}

//////////////////////////////////////////////////////////

void push(Stack *s, int item){
   insertNode(&(s->ll), 0, item);
}

int pop(Stack *s){
   int item;
   if(!isEmptyStack(s)){
    item = ((s->ll).head)->item;
    removeNode(&(s->ll), 0);
    return item;
   }
    return INT_MIN;
}

int peek(Stack *s){
   return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s){
   if ((s->ll).size == 0)
      return 1;
   return 0;
}

void enqueue(Queue *q, int item){
   insertNode(&(q->ll), q->ll.size, item);
}

int dequeue(Queue *q){
   int item;
   item = ((q->ll).head)->item;
   removeNode(&(q->ll), 0);
   return item;
}

int isEmptyQueue(Queue *q){
   if ((q->ll).size == 0)
      return 1;
   return 0;
}

/////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}
